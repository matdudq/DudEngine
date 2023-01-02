#include "mesh.hpp"

dud::Mesh::Mesh(dud::Device &device, const std::vector<Vertex> &vertices)
	: device(device) {
  CreateVertexBuffers(vertices);
}

dud::Mesh::~Mesh() {
  vkDestroyBuffer(device.GetDevice(), vertexBuffer, nullptr);
  vkFreeMemory(device.GetDevice(), vertexBufferMemory, nullptr);
}

void dud::Mesh::Bind(VkCommandBuffer commandBuffer) {
  VkBuffer buffers[] = {vertexBuffer};
  VkDeviceSize offsets[] = {0};
  vkCmdBindVertexBuffers(commandBuffer, 0, 1, buffers, offsets);
}

void dud::Mesh::Draw(VkCommandBuffer commandBuffer) const {
  vkCmdDraw(commandBuffer, vertexCount, 1, 0, 0);
}

void dud::Mesh::CreateVertexBuffers(const std::vector<Vertex> &vertices) {
  vertexCount = static_cast<uint32_t>(vertices.size());
  assert(vertexCount >= 3 && "Vertex count must be at least 3!");
  VkDeviceSize bufferSize = sizeof(vertices[0]) * vertexCount;
  device.CreateBuffer(bufferSize,
					  VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
					  VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT,
					  vertexBuffer,
					  vertexBufferMemory);

  void *data;
  vkMapMemory(device.GetDevice(), vertexBufferMemory, 0, bufferSize, 0, &data);
  memcpy(data, vertices.data(), static_cast<uint32_t>(bufferSize));
  vkUnmapMemory(device.GetDevice(), vertexBufferMemory);
}

std::vector<VkVertexInputBindingDescription> dud::Mesh::Vertex::GetBindingDescriptions() {
  return {{0, sizeof(Vertex), VK_VERTEX_INPUT_RATE_VERTEX}};
}

std::vector<VkVertexInputAttributeDescription> dud::Mesh::Vertex::GetAttributeDescriptions() {
  return {{0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, position)}};
}
