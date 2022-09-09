#pragma once

#define GLFW_INCLUDE_VULKAN
#include <string>
#include <GLFW//glfw3.h>

namespace dud{
    class DudWindow
    {
    public:
        DudWindow(int width, int height, std::string name);
        ~DudWindow();

        DudWindow(const DudWindow &) = delete;
        DudWindow &operator=(const DudWindow &) = delete;

        bool ShouldClose();

    private:
        void InitWindow();

        const int width;
        const int height;

        std::string windowName;

        GLFWwindow *window;
    };
}