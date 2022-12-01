#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include "dud_app.hpp"
#include "macros.hpp"
#include "dud_render_system.hpp"

#include <memory>

namespace dud {
    void App::run() {
        RenderSystem renderSystem{device, renderer.getSwapChainRenderPass()};

        while (!window.shouldClose()) {
            glfwPollEvents();

            if (auto commandBuffer = renderer.beginFrame()) {
                renderer.beginSwapChainRenderPass(commandBuffer);
                renderSystem.renderScene(commandBuffer, scene);
                renderer.endSwapChainRenderPass(commandBuffer);
                renderer.endFrame();
            }
        }

        vkDeviceWaitIdle(device.device());
    }

    App::App() {
        loadScene();
    }

    App::~App() {
    }

    void App::loadScene() {
        scene = std::make_unique<Scene>(device);
    }
}