#pragma once

#include "device.hpp"
#include "core.hpp"

#include <string>
#include <vector>

namespace dud {
struct PipelineConfigInfo {
  VkPipelineViewportStateCreateInfo viewportInfo;
  VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
  VkPipelineRasterizationStateCreateInfo rasterizationInfo;
  VkPipelineMultisampleStateCreateInfo multisampleInfo;
  VkPipelineColorBlendAttachmentState colorBlendAttachment;
  VkPipelineColorBlendStateCreateInfo colorBlendInfo;
  VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
  std::vector<VkDynamicState> dynamicStateEnables;
  VkPipelineDynamicStateCreateInfo dynamicStateInfo;
  VkPipelineLayout pipelineLayout = nullptr;
  VkRenderPass renderPass = nullptr;
  uint32_t subPass = 0;
};

class Pipeline {
 public:
  Pipeline(Device &device,
		   const PipelineConfigInfo &configInfo,
		   const std::string &vertexShaderPath,
		   const std::string &fragmentShaderPath);
  ~Pipeline();
  Pipeline(const Pipeline &) = delete;
  Pipeline &operator=(const Pipeline &) = delete;

  void Bind(VkCommandBuffer commandBuffer);
  static void DefaultPipelineConfigInfo(PipelineConfigInfo &configInfo);

 private:
  static std::vector<char> ReadFile(const std::string &filepath);
  void CreateGraphicsPipeline(const std::string &vertexShaderPath,
							  const std::string &fragmentShaderPath,
							  const PipelineConfigInfo &configInfo);
  void CreateShaderModule(const std::vector<char> &code,
						  VkShaderModule *shaderModule);

  Device &device;
  VkPipeline graphicsPipeline{};
  VkShaderModule vertShaderModule{};
  VkShaderModule fragmentShaderModule{};
};
}