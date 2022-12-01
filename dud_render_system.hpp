#pragma once

#include "dud_pipeline.hpp"
#include "dud_mesh.hpp"
#include "dud_core.hpp"
#include "dud_scene.hpp"

#include "memory"


namespace dud {
    class RenderSystem {
    private:
        Scope<Pipeline> pipeline;

        Device &device;
        VkPipelineLayout pipelineLayout;
    public:
        RenderSystem(Device &device, VkRenderPass renderPass);
        ~RenderSystem();

        RenderSystem(const RenderSystem &) = delete;
        RenderSystem &operator=(const RenderSystem &) = delete;

        void renderScene(VkCommandBuffer commandBuffer, const Scope<Scene> &scene);

    private:
        void createPipelineLayout();
        void createPipeline(VkRenderPass renderPass);
    };
}