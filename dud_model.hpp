#pragma once

#include "dud_device.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

namespace dud{
    class DudModel {
    public:
        struct Vertex{
            glm::vec2 position;
            glm::vec4 color;

            static std::vector<VkVertexInputBindingDescription> GetBindingDescriptions();
            static std::vector<VkVertexInputAttributeDescription> GetAttributeDescriptions();
        };

    private:
        DudDevice& device;
        VkBuffer vertexBuffer;
        VkDeviceMemory vertexBufferMemory;
        uint32_t vertexCount;

    public:
        DudModel(DudDevice &device, const std::vector<Vertex>& vertices);

        ~DudModel();

        DudModel(const DudModel &) = delete;
        DudModel &operator=(const DudModel &) = delete;
        void Bind(VkCommandBuffer commandBuffer);
        void Draw(VkCommandBuffer commandBuffer);
    private:
        void createVertexBuffers(const std::vector<Vertex>& vertices);
    };
}