#include "dud_app.hpp"
#include "macros.hpp"
#include <sstream>
#include <memory>

namespace dud {
    void DudApp::run() {
        while (!window.shouldClose()) {
            glfwPollEvents();
            drawFrame();
        }

        vkDeviceWaitIdle(device.device());
    }

    DudApp::DudApp() {
        loadModels();
        createPipelineLayout();
        createPipeline();
        createCommandBuffers();
    }

    DudApp::~DudApp() {
        vkDestroyPipelineLayout(device.device(), pipelineLayout, nullptr);
    }

    void DudApp::loadModels() {
        std::vector<DudModel::Vertex> vertices = {
            {{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}},
            {{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}},
            {{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}},
        };
        model = std::make_unique<DudModel>(device, vertices);
    }

    void DudApp::createPipelineLayout() {
        VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo{};
        pipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutCreateInfo.setLayoutCount = 0;
        pipelineLayoutCreateInfo.pSetLayouts = nullptr;
        pipelineLayoutCreateInfo.pushConstantRangeCount = 0;
        pipelineLayoutCreateInfo.pPushConstantRanges = nullptr;
        API_CALL_VALIDATE(vkCreatePipelineLayout(device.device(), &pipelineLayoutCreateInfo, nullptr, &pipelineLayout));
    }

    void DudApp::createPipeline() {
        auto pipelineConfig = DudPipeline::DefaultPipelineConfigInfo(swapChain.width(), swapChain.height());
        pipelineConfig.renderPass = swapChain.getRenderPass();
        pipelineConfig.pipelineLayout = pipelineLayout;
        pipeline = std::make_unique<DudPipeline>(device,
                                                 pipelineConfig,
                                                 "../shaders/default_vertex.vert.spv",
                                                 "../shaders/default_fragment.frag.spv");
    }

    void DudApp::createCommandBuffers() {
        commandBuffers.resize(swapChain.imageCount());
        VkCommandBufferAllocateInfo allocateInfo{};
        allocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocateInfo.commandPool = device.getCommandPool();
        allocateInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

        API_CALL_VALIDATE(vkAllocateCommandBuffers(device.device(), &allocateInfo, commandBuffers.data()));

        for (int i = 0; i < commandBuffers.size(); ++i) {
            VkCommandBufferBeginInfo beginInfo{};
            beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
            API_CALL_VALIDATE(vkBeginCommandBuffer(commandBuffers[i], &beginInfo));

            VkRenderPassBeginInfo renderPassBeginInfo{};
            renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
            renderPassBeginInfo.renderPass = swapChain.getRenderPass();
            renderPassBeginInfo.framebuffer = swapChain.getFrameBuffer(i);

            renderPassBeginInfo.renderArea.offset = {0, 0};
            renderPassBeginInfo.renderArea.extent = swapChain.getSwapChainExtent();

            std::array<VkClearValue, 2> clearValues{};
            clearValues[0].color = {0.1f, 0.1f, 0.1f, 1.0f};
            clearValues[1].depthStencil = {1.0f, 0};
            renderPassBeginInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
            renderPassBeginInfo.pClearValues = clearValues.data();

            vkCmdBeginRenderPass(commandBuffers[i], &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
            pipeline->Bind(commandBuffers[i]);
            model->Bind(commandBuffers[i]);
            model->Draw(commandBuffers[i]);
            vkCmdDraw(commandBuffers[i], 3, 1, 0, 0);

            vkCmdEndRenderPass(commandBuffers[i]);
            API_CALL_VALIDATE(vkEndCommandBuffer(commandBuffers[i]));
        }
    }

    void DudApp::drawFrame() {
        uint32_t imageIndex;
        auto result = swapChain.acquireNextImage(&imageIndex);
        if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR){
            throw std::runtime_error("Failed to acquire swap chain image!");
        }

        API_CALL_VALIDATE(swapChain.submitCommandBuffers(&commandBuffers[imageIndex], &imageIndex));
    }
}