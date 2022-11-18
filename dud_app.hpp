#pragma once

#include "dud_window.hpp"
#include "dud_pipeline.hpp"
#include "dud_swap_chain.hpp"

#include "memory"
#include "dud_model.hpp"

namespace dud {
    class DudApp {

    public:
        static constexpr int WIDTH = 800;
        static constexpr int HEIGHT = 800;
    private:
        DudWindow window{WIDTH, HEIGHT, "Main Window"};
        DudDevice device{window};
        DudSwapChain swapChain{device, window.getExtent()};
        std::unique_ptr<DudPipeline> pipeline;
        VkPipelineLayout pipelineLayout;
        std::vector<VkCommandBuffer> commandBuffers;
        std::unique_ptr<DudModel> model;
    public:
        DudApp();
        ~DudApp();

        DudApp(const DudApp &) = delete;
        DudApp &operator=(const DudApp &) = delete;

        void run();
    private:
        void loadModels();
        void createPipelineLayout();
        void createPipeline();
        void createCommandBuffers();
        void drawFrame();
        void recreateSwapChain();
        void recordCommandBuffer(int imageIndex);
    };
}