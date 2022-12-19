#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include "dud_app.hpp"
#include "macros.hpp"

#include <memory>

namespace dud {
    void App::run() {
        RenderSystem renderSystem{device, renderer.getSwapChainRenderPass()};
        Camera camera{};

        float aspectRatio = renderer.getExtendAspectRatio();
        //camera.SetOrthographicProjection(-aspectRatio, aspectRatio, -1, 1, -1, 1);
        camera.SetPerspectiveProjection(glm::radians(50.f), aspectRatio, 0.1f, 10.f);

        while (!window.shouldClose()) {
            glfwPollEvents();
            systemContainer.OnUpdate(scene->registry);
            render(renderSystem, camera);
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

    void App::render(const RenderSystem &renderSystem, const Camera &camera) {
        if (auto commandBuffer = renderer.beginFrame()) {
            renderer.beginSwapChainRenderPass(commandBuffer);
            renderSystem.renderScene(commandBuffer, scene, camera);
            renderer.endSwapChainRenderPass(commandBuffer);
            renderer.endFrame();
        }
    }
}