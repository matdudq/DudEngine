#pragma once

#define GLFW_INCLUDE_VULKAN
#include <string>
#include <GLFW//glfw3.h>

namespace dud{
    class Window
    {
    private:
        bool framebufferResized = false;
        int width;
        int height;

        std::string windowName;

        GLFWwindow *window;

    public:
        Window(int width, int height, std::string name);
        ~Window();

        Window(const Window &) = delete;
        Window &operator=(const Window &) = delete;

        bool shouldClose();
        bool wasWindowResized();
        void resetWindowResizedFlag();
        VkExtent2D getExtent() const { return {static_cast<uint32_t>(width), static_cast<uint32_t>(height)}; }
        void createWindowSurface(VkInstance pT, VkSurfaceKHR *pT1);

    private:
        static void frameBufferResizeCallback(GLFWwindow *window, int width, int height);
        void initWindow();
    };
}