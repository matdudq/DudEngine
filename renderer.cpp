#include "renderer.hpp"
#include "macros.hpp"
#include "components/transform_component.hpp"
#include "components/mesh_component.hpp"

#include <sstream>
#include <memory>

namespace dud {
Renderer::Renderer(Window &window, Device &device) : window(window),
													 device(device),
													 isFrameStarted(false),
													 currentFrameIndex(0),
													 currentImageIndex(0) {
  RecreateSwapChain();
  CreateCommandBuffers();
}

Renderer::~Renderer() {
  FreeCommandBuffers();
}

void Renderer::CreateCommandBuffers() {
  commandBuffers.resize(SwapChain::maxFramesInFlight);
  VkCommandBufferAllocateInfo allocateInfo{};
  allocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  allocateInfo.commandPool = device.GetCommandPool();
  allocateInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

  API_CALL_VALIDATE(vkAllocateCommandBuffers(device.GetDevice(),
											 &allocateInfo,
											 commandBuffers.data()));
}

void Renderer::FreeCommandBuffers() {
  vkFreeCommandBuffers(device.GetDevice(),
					   device.GetCommandPool(),
					   static_cast<float>(commandBuffers.size()),
					   commandBuffers.data());
  commandBuffers.clear();
}

void Renderer::RecreateSwapChain() {
  auto extend = window.GetExtent();
  while (extend.width == 0 || extend.height == 0) {
	extend = window.GetExtent();
	glfwWaitEvents();
  }

  vkDeviceWaitIdle(device.GetDevice());
  if (swapChain == nullptr) {
	swapChain = std::make_unique<SwapChain>(device, extend);
  } else {
	Ref<SwapChain> oldSwapChain = std::move(swapChain);
	swapChain = std::make_unique<SwapChain>(device, extend, oldSwapChain);

	if (!oldSwapChain->CompareSwapFormats(*swapChain.get())) {
	  throw std::runtime_error("Swap chain image(or depth) format has changed!");
	}
  }
  //CreatePipeline();
}

VkCommandBuffer Renderer::BeginFrame() {
  assert(!isFrameStarted && "Can't call BeginFrame when frame already started!");
  auto result = swapChain->AcquireNextImage(&currentImageIndex);
  if (result == VK_ERROR_OUT_OF_DATE_KHR) {
	RecreateSwapChain();
	return nullptr;
  }

  if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
	throw std::runtime_error("Failed to acquire swap chain image!");
  }
  isFrameStarted = true;

  auto commandBuffer = GetCurrentCommandBuffer();

  VkCommandBufferBeginInfo beginInfo{};
  beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  API_CALL_VALIDATE(vkBeginCommandBuffer(commandBuffer, &beginInfo));

  return commandBuffer;
}

void Renderer::EndFrame() {
  assert(isFrameStarted && "Can't call EndFrame when frame is not started!");
  auto commandBuffer = GetCurrentCommandBuffer();
  API_CALL_VALIDATE(vkEndCommandBuffer(commandBuffer));

  auto result = swapChain->SubmitCommandBuffers(&commandBuffer, &currentImageIndex);
  if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR
	  || window.WasWindowResized()) {
	window.ResetWindowResizedFlag();
	RecreateSwapChain();
  } else {
	API_CALL_VALIDATE(result);
  }

  isFrameStarted = false;
  currentFrameIndex = (currentFrameIndex + 1) % SwapChain::maxFramesInFlight;
}

void Renderer::BeginSwapChainRenderPass(VkCommandBuffer commandBuffer) {
  assert(isFrameStarted
			 && "Can't call BeginSwapChainRenderPass when frame is not started!");
  assert(commandBuffer == GetCurrentCommandBuffer() &&
	  "Can't begin render pass on command buffer from a different frame!");

  VkRenderPassBeginInfo renderPassBeginInfo{};
  renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
  renderPassBeginInfo.renderPass = swapChain->GetRenderPass();
  renderPassBeginInfo.framebuffer =
	  swapChain->GetFrameBuffer(currentImageIndex);

  renderPassBeginInfo.renderArea.offset = {0, 0};
  renderPassBeginInfo.renderArea.extent = swapChain->GetExtent();

  std::array<VkClearValue, 2> clearValues{};
  clearValues[0].color = {0.1f, 0.1f, 0.1f, 1.0f};
  clearValues[1].depthStencil = {1.0f, 0};
  renderPassBeginInfo.clearValueCount =
	  static_cast<uint32_t>(clearValues.size());
  renderPassBeginInfo.pClearValues = clearValues.data();


  vkCmdBeginRenderPass(commandBuffer,
					   &renderPassBeginInfo,
					   VK_SUBPASS_CONTENTS_INLINE);

  VkViewport viewport{};
  viewport.x = 0.0f;
  viewport.y = 0.0f;
  viewport.width = static_cast<float>(swapChain->GetExtent().width);
  viewport.height = static_cast<float>(swapChain->GetExtent().height);
  viewport.minDepth = 0.0f;
  viewport.maxDepth = 1.0f;
  VkRect2D scissor{{0, 0}, swapChain->GetExtent()};
  vkCmdSetViewport(commandBuffer, 0, 1, &viewport);
  vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

}

void Renderer::EndSwapChainRenderPass(VkCommandBuffer commandBuffer) {
  assert(isFrameStarted && "Can't call EndSwapChainRenderPass when frame is not started!");
  assert(commandBuffer == GetCurrentCommandBuffer() &&
	  "Can't end render pass on command buffer from a different frame!");

  vkCmdEndRenderPass(commandBuffer);
}
}