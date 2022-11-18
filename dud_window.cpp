#include "dud_window.hpp"
#include "macros.hpp"

namespace dud{
    DudWindow::DudWindow(int width, int height, std::string name) : width(width), height(height), windowName(name) {
        initWindow();
    }

    DudWindow::~DudWindow() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void DudWindow::initWindow() {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

        window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
        glfwSetWindowUserPointer(window, this);
        glfwSetFramebufferSizeCallback(window, frameBufferResizeCallback);
    }

    bool DudWindow::shouldClose() {
        return glfwWindowShouldClose(window);
    }

    void DudWindow::createWindowSurface(VkInstance instance, VkSurfaceKHR *surface) {
        API_CALL_VALIDATE(glfwCreateWindowSurface(instance, window, nullptr, surface));
    }

    void DudWindow::resetWindowResizedFlag() {
        framebufferResized = false;
    }

    bool DudWindow::wasWindowResized() {
        return framebufferResized;
    }

    void DudWindow::frameBufferResizeCallback(GLFWwindow *window, int width, int height) {
        auto dudWindow = reinterpret_cast<DudWindow*>(glfwGetWindowUserPointer(window));
        dudWindow->framebufferResized = true;
        dudWindow->width = width;
        dudWindow->height = height;
    }
}

