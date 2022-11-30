#include "dud_model.hpp"

dud::Model::Model(dud::Device &device, const std::vector<Vertex> &vertices) : device(device){
    createVertexBuffers(vertices);
}

dud::Model::~Model() {
    vkDestroyBuffer(device.device(), vertexBuffer, nullptr);
    vkFreeMemory(device.device(), vertexBufferMemory, nullptr);
}

void dud::Model::bind(VkCommandBuffer commandBuffer) {
    VkBuffer buffers[] = {vertexBuffer};
    VkDeviceSize offsets[] = {0};
    vkCmdBindVertexBuffers(commandBuffer, 0, 1, buffers, offsets);
}

void dud::Model::draw(VkCommandBuffer commandBuffer) {
    vkCmdDraw(commandBuffer, vertexCount, 1, 0, 0);
}

void dud::Model::createVertexBuffers(const std::vector<Vertex>& vertices) {
    vertexCount = static_cast<uint32_t>(vertices.size());
    assert(vertexCount >= 3 && "Vertex count must be at least 3!");
    VkDeviceSize bufferSize = sizeof(vertices[0]) * vertexCount;
    device.createBuffer(bufferSize,
                        VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT,
                        vertexBuffer,
                        vertexBufferMemory);

    void *data;
    vkMapMemory(device.device(), vertexBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, vertices.data(), static_cast<uint32_t>(bufferSize));
    vkUnmapMemory(device.device(), vertexBufferMemory);
}

std::vector<VkVertexInputBindingDescription> dud::Model::Vertex::GetBindingDescriptions() {
    return {{0, sizeof(Vertex), VK_VERTEX_INPUT_RATE_VERTEX}};
}

std::vector<VkVertexInputAttributeDescription> dud::Model::Vertex::GetAttributeDescriptions() {
    return {{0, 0, VK_FORMAT_R32G32_SFLOAT, offsetof(Vertex, position)},
            {1, 0, VK_FORMAT_R32G32B32A32_SFLOAT, offsetof(Vertex, color)}};
}
