#pragma once

#include "dud_device.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

namespace dud{
    class Model {
    public:
        struct Vertex{
            glm::vec2 position;
            glm::vec4 color;

            static std::vector<VkVertexInputBindingDescription> GetBindingDescriptions();
            static std::vector<VkVertexInputAttributeDescription> GetAttributeDescriptions();
        };

    private:
        Device& device;
        VkBuffer vertexBuffer;
        VkDeviceMemory vertexBufferMemory;
        uint32_t vertexCount;

    public:
        Model(Device &device, const std::vector<Vertex>& vertices);

        ~Model();

        Model(const Model &) = delete;
        Model &operator=(const Model &) = delete;
        void bind(VkCommandBuffer commandBuffer);
        void draw(VkCommandBuffer commandBuffer);
    private:
        void createVertexBuffers(const std::vector<Vertex>& vertices);
    };
}