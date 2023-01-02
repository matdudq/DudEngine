#pragma once

#include <string>

#include <glfw3.h>
#include <vulkan/vulkan_core.h>

#define GLFW_INCLUDE_VULKAN

namespace dud {
class Window {
 public:
  Window(int width, int height, std::string name);
  ~Window();

  Window(const Window &) = delete;
  Window &operator=(const Window &) = delete;

  bool ShouldClose();
  bool WasWindowResized();
  void ResetWindowResizedFlag();
  VkExtent2D GetExtent() const {
	return {static_cast<uint32_t>(width), static_cast<uint32_t>(height)};
  }
  void CreateWindowSurface(VkInstance pT, VkSurfaceKHR *pT1);

 private:
  static void FrameBufferResizeCallback(GLFWwindow *window,
										int width,
										int height);

  void InitWindow();

  bool framebufferResized = false;
  int width;
  int height;

  std::string windowName;

  GLFWwindow *window;
};
}