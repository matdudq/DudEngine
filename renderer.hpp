#pragma once

#include "window.hpp"
#include "swap_chain.hpp"

#include "memory"
#include "mesh.hpp"
#include "core.hpp"
#include "scene.hpp"

namespace dud {
class Renderer {

 public:
  Renderer(Window &window, Device &device);
  ~Renderer();
  Renderer(const Renderer &) = delete;
  Renderer &operator=(const Renderer &) = delete;

  VkCommandBuffer BeginFrame();
  void EndFrame();
  void BeginSwapChainRenderPass(VkCommandBuffer commandBuffer);
  void EndSwapChainRenderPass(VkCommandBuffer commandBuffer);

  bool IsFrameInProgress() const { return isFrameStarted; }

  float GetExtendAspectRatio() const { return swapChain->GetExtentAspectRatio(); }

  VkRenderPass GetSwapChainRenderPass() const {
	return swapChain->GetRenderPass();
  }

  VkCommandBuffer GetCurrentCommandBuffer() const {
	assert(
		isFrameStarted && "Cannot get command buffer when frame not started!");
	return commandBuffers[currentFrameIndex];
  }

 private:
  void CreateCommandBuffers();
  void FreeCommandBuffers();
  void RecreateSwapChain();

  Window &window;
  Device &device;

  Scope<SwapChain> swapChain;
  std::vector<VkCommandBuffer> commandBuffers;

  uint32_t currentImageIndex;
  int currentFrameIndex;
  bool isFrameStarted;
};
}
