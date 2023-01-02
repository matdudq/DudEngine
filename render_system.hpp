#pragma once

#include "pipeline.hpp"
#include "mesh.hpp"
#include "core.hpp"
#include "scene.hpp"
#include "renderer.hpp"

namespace dud {
class RenderSystem {
 public:
  RenderSystem(Device &device, VkRenderPass renderPass);
  ~RenderSystem();

  RenderSystem(const RenderSystem &) = delete;
  RenderSystem &operator=(const RenderSystem &) = delete;

  void RenderScene(VkCommandBuffer commandBuffer,
				   const Scope<Scene> &scene,
				   const Renderer &renderer) const;

 private:
  void CreatePipelineLayout();
  void CreatePipeline(VkRenderPass renderPass);

  Scope<Pipeline> pipeline;

  Device &device;
  VkPipelineLayout pipelineLayout;
};
}