#pragma once

#include "dud_window.hpp"
#include "dud_swap_chain.hpp"

#include "memory"
#include "dud_mesh.hpp"
#include "dud_core.hpp"
#include "dud_scene.hpp"

namespace dud {
    class Renderer {
    private:
        Window &window;
        Device &device;

        Scope<SwapChain> swapChain;
        std::vector<VkCommandBuffer> commandBuffers;

        uint32_t currentImageIndex;
        int currentFrameIndex;
        bool isFrameStarted;
    public:
        Renderer(Window &window, Device &device);

        ~Renderer();

        Renderer(const Renderer &) = delete;

        Renderer &operator=(const Renderer &) = delete;

        bool isFrameInProgress() const { return isFrameStarted; }

        float getExtendAspectRatio() const { return swapChain->getExtentAspectRatio(); }

        VkRenderPass getSwapChainRenderPass() const {
            return swapChain->getRenderPass();
        }

        VkCommandBuffer getCurrentCommandBuffer() const {
            assert(isFrameStarted && "Cannot get command buffer when frame not started!");
            return commandBuffers[currentFrameIndex];
        }

        int getFrameIndex() const {
            assert(isFrameStarted && "Cannot get frame index when frame not started!");
            return currentFrameIndex;
        }

        VkCommandBuffer beginFrame();

        void endFrame();

        void beginSwapChainRenderPass(VkCommandBuffer commandBuffer);

        void endSwapChainRenderPass(VkCommandBuffer commandBuffer);

    private:
        void createCommandBuffers();

        void freeCommandBuffers();

        void recreateSwapChain();

    };
}
