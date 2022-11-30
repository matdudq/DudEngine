#pragma once

#include "dud_window.hpp"
#include "dud_pipeline.hpp"
#include "dud_swap_chain.hpp"

#include "memory"
#include "dud_mesh.hpp"
#include "dud_core.hpp"
#include "dud_scene.hpp"

namespace dud {
    class App {

    public:
        static constexpr int WIDTH = 800;
        static constexpr int HEIGHT = 800;
    private:
        Window window{WIDTH, HEIGHT, "Main Window"};
        Device device{window};
        Scope<SwapChain> swapChain;
        Scope<Pipeline> pipeline;
        VkPipelineLayout pipelineLayout;
        std::vector<VkCommandBuffer> commandBuffers;
        Scope<Scene> scene;

    public:
        App();
        ~App();

        App(const App &) = delete;
        App &operator=(const App &) = delete;

        void run();
    private:
        void loadScene();
        void createPipelineLayout();
        void createPipeline();
        void createCommandBuffers();
        void freeCommandBuffers();
        void drawFrame();
        void recreateSwapChain();
        void recordCommandBuffer(int imageIndex);
        void renderScene(VkCommandBuffer commandBuffer);
    };
}