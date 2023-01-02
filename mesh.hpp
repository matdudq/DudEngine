#pragma once

#include "device.hpp"

#include <glm/glm.hpp>

namespace dud {
class Mesh {
 public:
  struct Vertex {
	glm::vec3 position;
	glm::vec3 color;

	static std::vector<VkVertexInputBindingDescription> GetBindingDescriptions();
	static std::vector<VkVertexInputAttributeDescription> GetAttributeDescriptions();
  };

  Mesh(Device &device, const std::vector<Vertex> &vertices);
  ~Mesh();
  Mesh(const Mesh &) = delete;
  Mesh &operator=(const Mesh &) = delete;

  void Bind(VkCommandBuffer commandBuffer);
  void Draw(VkCommandBuffer commandBuffer) const;

 private:
  void CreateVertexBuffers(const std::vector<Vertex> &vertices);

  Device &device;
  VkBuffer vertexBuffer{};
  VkDeviceMemory vertexBufferMemory{};
  uint32_t vertexCount{};
};
}