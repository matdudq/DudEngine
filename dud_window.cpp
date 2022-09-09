#include "dud_window.hpp"

namespace dud{
    DudWindow::DudWindow(int width, int height, std::string name) : width(width), height(height), windowName(name) {
        InitWindow();
    }

    DudWindow::~DudWindow() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void DudWindow::InitWindow() {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
    }

    bool DudWindow::ShouldClose() {
        return glfwWindowShouldClose(window);
    }
}

