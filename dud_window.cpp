#include "dud_window.hpp"
#include "macros.hpp"

namespace dud{
    Window::Window(int width, int height, std::string name) : width(width), height(height), windowName(name) {
        initWindow();
    }

    Window::~Window() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void Window::initWindow() {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

        window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
        glfwSetWindowUserPointer(window, this);
        glfwSetFramebufferSizeCallback(window, frameBufferResizeCallback);
    }

    bool Window::shouldClose() {
        return glfwWindowShouldClose(window);
    }

    void Window::createWindowSurface(VkInstance instance, VkSurfaceKHR *surface) {
        API_CALL_VALIDATE(glfwCreateWindowSurface(instance, window, nullptr, surface));
    }

    void Window::resetWindowResizedFlag() {
        framebufferResized = false;
    }

    bool Window::wasWindowResized() {
        return framebufferResized;
    }

    void Window::frameBufferResizeCallback(GLFWwindow *window, int width, int height) {
        auto dudWindow = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
        dudWindow->framebufferResized = true;
        dudWindow->width = width;
        dudWindow->height = height;
    }
}

