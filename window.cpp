#define GLFW_INCLUDE_VULKAN

#include "window.hpp"
#include "macros.hpp"

#include <glfw3.h>

namespace dud {
Window::Window(int width, int height, std::string name)
	: width(width), height(height), windowName(name) {
  InitWindow();
}

Window::~Window() {
  glfwDestroyWindow(window);
  glfwTerminate();
}

void Window::InitWindow() {
  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

  window =
	  glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
  glfwSetWindowUserPointer(window, this);
  glfwSetFramebufferSizeCallback(window, FrameBufferResizeCallback);
}

bool Window::ShouldClose() {
  return glfwWindowShouldClose(window);
}

void Window::CreateWindowSurface(VkInstance pT, VkSurfaceKHR *pT1) {
  API_CALL_VALIDATE(glfwCreateWindowSurface(pT, window, nullptr, pT1));
}

void Window::ResetWindowResizedFlag() {
  framebufferResized = false;
}

bool Window::WasWindowResized() {
  return framebufferResized;
}

void Window::FrameBufferResizeCallback(GLFWwindow *window,
									   int width,
									   int height) {
  auto dudWindow = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
  dudWindow->framebufferResized = true;
  dudWindow->width = width;
  dudWindow->height = height;
}
}

