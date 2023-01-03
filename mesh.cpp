#include "mesh.hpp"

dud::Mesh::Mesh(dud::Device &device, const dud::Mesh::ModelBuilder &builder) : device(device) {
  CreateVertexBuffers(builder.vertices);
  CreateIndexBuffers(builder.indices);
}

dud::Mesh::~Mesh() {
  vkDestroyBuffer(device.GetDevice(), vertexBuffer, nullptr);
  vkFreeMemory(device.GetDevice(), vertexBufferMemory, nullptr);

  if(hasIndexBuffer){
	vkDestroyBuffer(device.GetDevice(), indexBuffer, nullptr);
	vkFreeMemory(device.GetDevice(), indexBufferMemory, nullptr);
  }
}

void dud::Mesh::Bind(VkCommandBuffer commandBuffer) {
  VkBuffer buffers[] = {vertexBuffer};
  VkDeviceSize offsets[] = {0};
  vkCmdBindVertexBuffers(commandBuffer, 0, 1, buffers, offsets);

  if(hasIndexBuffer){
	vkCmdBindIndexBuffer(commandBuffer, indexBuffer, 0 , VK_INDEX_TYPE_UINT32);
  }
}

void dud::Mesh::Draw(VkCommandBuffer commandBuffer) const {
  if(hasIndexBuffer){
	vkCmdDrawIndexed(commandBuffer, indexCount, 1, 0, 0, 0);
  }
  else{
	vkCmdDraw(commandBuffer, vertexCount, 1, 0, 0);
  }
}

void dud::Mesh::CreateVertexBuffers(const std::vector<Vertex> &vertices) {
  vertexCount = static_cast<uint32_t>(vertices.size());
  assert(vertexCount >= 3 && "Vertex count must be at least 3!");
  VkDeviceSize bufferSize = sizeof(vertices[0]) * vertexCount;

  VkBuffer stagingBuffer;
  VkDeviceMemory stagingBufferMemory;

  device.CreateBuffer(bufferSize,
					  VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
					  VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
					  stagingBuffer,
					  stagingBufferMemory);

  void *data;
  vkMapMemory(device.GetDevice(), stagingBufferMemory, 0, bufferSize, 0, &data);
  memcpy(data, vertices.data(), static_cast<uint32_t>(bufferSize));
  vkUnmapMemory(device.GetDevice(), stagingBufferMemory);

  device.CreateBuffer(bufferSize,
					  VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
					  VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT ,
					  vertexBuffer,
					  vertexBufferMemory);
  device.CopyBuffer(stagingBuffer, vertexBuffer, bufferSize);

  vkDestroyBuffer(device.GetDevice(), stagingBuffer, nullptr);
  vkFreeMemory(device.GetDevice(), stagingBufferMemory, nullptr);
}

void dud::Mesh::CreateIndexBuffers(std::vector<uint32_t> indices) {
  indexCount = static_cast<uint32_t>(indices.size());
  hasIndexBuffer = indexCount > 0;
  if(!hasIndexBuffer){
	return;
  }

  VkDeviceSize bufferSize = sizeof(indices[0]) * indexCount;
  VkBuffer stagingBuffer;
  VkDeviceMemory stagingBufferMemory;

  device.CreateBuffer(bufferSize,
					  VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
					  VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
					  stagingBuffer,
					  stagingBufferMemory);

  void *data;
  vkMapMemory(device.GetDevice(), stagingBufferMemory, 0, bufferSize, 0, &data);
  memcpy(data, indices.data(), static_cast<uint32_t>(bufferSize));
  vkUnmapMemory(device.GetDevice(), stagingBufferMemory);

  device.CreateBuffer(bufferSize,
					  VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
					  VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT ,
					  indexBuffer,
					  indexBufferMemory);
  device.CopyBuffer(stagingBuffer, indexBuffer, bufferSize);

  vkDestroyBuffer(device.GetDevice(), stagingBuffer, nullptr);
  vkFreeMemory(device.GetDevice(), stagingBufferMemory, nullptr);
}

std::vector<VkVertexInputBindingDescription> dud::Mesh::Vertex::GetBindingDescriptions() {
  return {{0, sizeof(Vertex), VK_VERTEX_INPUT_RATE_VERTEX}};
}

std::vector<VkVertexInputAttributeDescription> dud::Mesh::Vertex::GetAttributeDescriptions() {
  return {{0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, position)}};
}
