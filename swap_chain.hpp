#pragma once

#include "device.hpp"
#include "core.hpp"

#include <vulkan/vulkan.h>

#include <string>
#include <vector>
#include <memory>

namespace dud {

class SwapChain {
 public:
  static constexpr int maxFramesInFlight = 2;

  SwapChain(Device &deviceRef, VkExtent2D windowExtent);
  SwapChain(Device &deviceRef,
			VkExtent2D windowExtent,
			Ref<SwapChain> previous);
  ~SwapChain();
  SwapChain(const SwapChain &) = delete;
  SwapChain &operator=(const SwapChain &) = delete;

  VkFormat FindDepthFormat();

  VkResult AcquireNextImage(uint32_t *imageIndex);

  VkResult SubmitCommandBuffers(const VkCommandBuffer *buffers,
								uint32_t *imageIndex);

  bool CompareSwapFormats(const SwapChain &chain) const {
	return chain.swapChainImageFormat == swapChainImageFormat &&
		chain.swapChainDepthFormat == swapChainDepthFormat;
  }

  VkFramebuffer GetFrameBuffer(int index) { return swapChainFramebuffers[index]; }

  VkRenderPass GetRenderPass() { return renderPass; }

  VkImageView GetImageView(int index) { return swapChainImageViews[index]; }

  size_t ImageCount() { return swapChainImages.size(); }

  VkFormat GetImageFormat() { return swapChainImageFormat; }

  VkExtent2D GetExtent() { return swapChainExtent; }

  float GetExtentAspectRatio() const {
	return static_cast<float>(swapChainExtent.width)
		/ static_cast<float>(swapChainExtent.height);
  }

  uint32_t Width() const { return swapChainExtent.width; }

  uint32_t Height() const { return swapChainExtent.height; }

 private:
  void Init();
  void CreateSwapChain();
  void CreateImageViews();
  void CreateDepthResources();
  void CreateRenderPass();
  void CreateFrameBuffers();
  void CreateSyncObjects();

  VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<
	  VkSurfaceFormatKHR> &availableFormats);
  VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);
  VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);

  VkFormat swapChainImageFormat;
  VkFormat swapChainDepthFormat;
  VkExtent2D swapChainExtent;

  std::vector<VkFramebuffer> swapChainFramebuffers;
  VkRenderPass renderPass;

  std::vector<VkImage> depthImages;
  std::vector<VkDeviceMemory> depthImageMemorys;
  std::vector<VkImageView> depthImageViews;
  std::vector<VkImage> swapChainImages;
  std::vector<VkImageView> swapChainImageViews;

  Device &device;
  VkExtent2D windowExtent;

  VkSwapchainKHR swapChain;
  Ref<SwapChain> oldSwapChain;
  std::vector<VkSemaphore> imageAvailableSemaphores;
  std::vector<VkSemaphore> renderFinishedSemaphores;
  std::vector<VkFence> inFlightFences;
  std::vector<VkFence> imagesInFlight;
  size_t currentFrame = 0;
};
}
