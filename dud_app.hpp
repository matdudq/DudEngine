#pragma once

#include "dud_window.hpp"
#include "dud_pipeline.hpp"
#include "dud_swap_chain.hpp"

#include "memory"
#include "dud_model.hpp"

namespace dud {
    class App {

    public:
        static constexpr int WIDTH = 800;
        static constexpr int HEIGHT = 800;
    private:
        Window window{WIDTH, HEIGHT, "Main Window"};
        Device device{window};
        std::unique_ptr<SwapChain> swapChain;
        std::unique_ptr<Pipeline> pipeline;
        VkPipelineLayout pipelineLayout;
        std::vector<VkCommandBuffer> commandBuffers;
        std::unique_ptr<Model> model;
    public:
        App();
        ~App();

        App(const App &) = delete;
        App &operator=(const App &) = delete;

        void run();
    private:
        void loadModels();
        void createPipelineLayout();
        void createPipeline();
        void createCommandBuffers();
        void freeCommandBuffers();
        void drawFrame();
        void recreateSwapChain();
        void recordCommandBuffer(int imageIndex);
    };
}