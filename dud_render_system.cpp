#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include "dud_render_system.hpp"
#include "macros.hpp"
#include "components/dud_transform_component.hpp"
#include "components/dud_mesh_component.hpp"

#include <memory>

namespace dud {
    struct SimplePushConstantData {
        glm::mat4 transform;
        alignas(128) glm::vec3 color;
    };

    RenderSystem::RenderSystem(Device &device, VkRenderPass renderPass) : device(device) {
        createPipelineLayout();
        createPipeline(renderPass);
    }

    RenderSystem::~RenderSystem() {
        vkDestroyPipelineLayout(device.device(), pipelineLayout, nullptr);
    }

    void RenderSystem::createPipelineLayout() {
        VkPushConstantRange pushConstantRange{};
        pushConstantRange.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT | VK_SHADER_STAGE_VERTEX_BIT;
        pushConstantRange.offset = 0;
        pushConstantRange.size = sizeof(SimplePushConstantData);

        VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo{};
        pipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutCreateInfo.setLayoutCount = 0;
        pipelineLayoutCreateInfo.pSetLayouts = nullptr;
        pipelineLayoutCreateInfo.pushConstantRangeCount = 1;
        pipelineLayoutCreateInfo.pPushConstantRanges = &pushConstantRange;
        API_CALL_VALIDATE(vkCreatePipelineLayout(device.device(), &pipelineLayoutCreateInfo, nullptr, &pipelineLayout));
    }



    void RenderSystem::createPipeline(VkRenderPass renderPass) {
        assert(pipelineLayout != nullptr && "Cannot create pipeline before pipeline layout!");

        PipelineConfigInfo pipelineConfig{};
        Pipeline::defaultPipelineConfigInfo(pipelineConfig);
        pipelineConfig.renderPass = renderPass;
        pipelineConfig.pipelineLayout = pipelineLayout;
        pipeline = std::make_unique<Pipeline>(device,
                                              pipelineConfig,
                                              "../shaders/default_vertex.vert.spv",
                                              "../shaders/default_fragment.frag.spv");
    }

    void RenderSystem::renderScene(VkCommandBuffer commandBuffer, const Scope<Scene> &scene) {
        pipeline->bind(commandBuffer);

        auto group = scene->registry.group<TransformComponent>(entt::get<MeshComponent>);
        for (auto entity : group)
        {
            const auto& [transform, mesh] = group.get<TransformComponent,MeshComponent>(entity);

            SimplePushConstantData push{};
            push.transform = transform.Transform;
            push.color = mesh.color;

            vkCmdPushConstants(commandBuffer,
                               pipelineLayout,
                               VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
                               0,
                               sizeof(SimplePushConstantData),
                               &push);

            mesh.model->bind(commandBuffer);
            mesh.model->draw(commandBuffer);
        }
    }
}