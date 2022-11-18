#pragma once

#include <string>
#include <vector>
#include "dud_device.hpp"

namespace dud {

    struct PipelineConfigInfo {
        VkViewport viewport;
        VkRect2D scissor;
        VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
        VkPipelineRasterizationStateCreateInfo rasterizationInfo;
        VkPipelineMultisampleStateCreateInfo multisampleInfo;
        VkPipelineColorBlendAttachmentState colorBlendAttachment;
        VkPipelineColorBlendStateCreateInfo colorBlendInfo;
        VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
        VkPipelineLayout pipelineLayout = nullptr;
        VkRenderPass renderPass = nullptr;
        uint32_t subpass = 0;
    };

    class DudPipeline {
    public:

    private:
        DudDevice &device;
        VkPipeline graphicsPipeline;
        VkShaderModule vertShaderModule;
        VkShaderModule fragmentShaderModule;

    public:
        DudPipeline(DudDevice &device, const PipelineConfigInfo &configInfo, const std::string &vertexShaderPath,
                    const std::string &fragmentShaderPath);

        ~DudPipeline();

        DudPipeline(const DudPipeline &) = delete;
        DudPipeline &operator=(const DudPipeline &) = delete;

        void Bind(VkCommandBuffer commandBuffer);
        static PipelineConfigInfo DefaultPipelineConfigInfo(uint32_t width, uint32_t height);

    private:
        static std::vector<char> readFile(const std::string &filepath);

        void createGraphicsPipeline(const std::string &vertexShaderPath, const std::string &fragmentShaderPath,
                                    const PipelineConfigInfo configInfo);

        void createShaderModule(const std::vector<char> &code, VkShaderModule *shaderModule);
    };
}