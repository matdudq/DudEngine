#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <glm/glm.hpp>

#include "render_system.hpp"
#include "macros.hpp"
#include "components/transform_component.hpp"
#include "components/mesh_component.hpp"

#include <memory>

namespace dud {
struct SimplePushConstantData {
  glm::mat4 transform;
  alignas(64) glm::vec4 color;
};

RenderSystem::RenderSystem(Device &device, VkRenderPass renderPass) : device(
	device) {
  CreatePipelineLayout();
  CreatePipeline(renderPass);
}

RenderSystem::~RenderSystem() {
  vkDestroyPipelineLayout(device.GetDevice(), pipelineLayout, nullptr);
}

void RenderSystem::CreatePipelineLayout() {
  VkPushConstantRange pushConstantRange{};
  pushConstantRange.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT | VK_SHADER_STAGE_VERTEX_BIT;
  pushConstantRange.offset = 0;
  pushConstantRange.size = sizeof(SimplePushConstantData);

  VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo{};
  pipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
  pipelineLayoutCreateInfo.setLayoutCount = 0;
  pipelineLayoutCreateInfo.pSetLayouts = nullptr;
  pipelineLayoutCreateInfo.pushConstantRangeCount = 1;
  pipelineLayoutCreateInfo.pPushConstantRanges = &pushConstantRange;
  API_CALL_VALIDATE(vkCreatePipelineLayout(device.GetDevice(),
										   &pipelineLayoutCreateInfo,
										   nullptr,
										   &pipelineLayout));
}

void RenderSystem::CreatePipeline(VkRenderPass renderPass) {
  assert(pipelineLayout != nullptr
			 && "Cannot create pipeline before pipeline layout!");

  PipelineConfigInfo pipelineConfig{};
  Pipeline::DefaultPipelineConfigInfo(pipelineConfig);
  pipelineConfig.renderPass = renderPass;
  pipelineConfig.pipelineLayout = pipelineLayout;
  pipeline = std::make_unique<Pipeline>(device,
										pipelineConfig,
										"../shaders/default_vertex.vert.spv",
										"../shaders/default_fragment.frag.spv");
}

void RenderSystem::RenderScene(VkCommandBuffer commandBuffer,
							   const Scope<Scene> &scene,
							   const Renderer &renderer) const {
  pipeline->Bind(commandBuffer);

  auto group = scene->registry.group<TransformComponent>(entt::get<MeshComponent>);

  auto cameraComponent = scene->GetPrimaryCamera();
  float aspectRatio = renderer.GetExtendAspectRatio();
  cameraComponent->SetPerspectiveProjection(glm::radians(50.f),
											aspectRatio,
											0.1f,
											100.f);

  cameraComponent->SetViewTarget(glm::vec3(0., 0., 0.f),
								 glm::vec3(0.0f, 0.0f, 3.5f));
  auto cameraProjectionView = cameraComponent->GetProjectionView();

  for (auto entity : group) {
	const auto &[transform, mesh] = group.get<TransformComponent, MeshComponent>(entity);

	SimplePushConstantData push{};
	push.transform = cameraProjectionView * transform.GetTransform();
	push.color = mesh.color;

	vkCmdPushConstants(commandBuffer,
					   pipelineLayout,
					   VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
					   0,
					   sizeof(SimplePushConstantData),
					   &push);

	mesh.model->Bind(commandBuffer);
	mesh.model->Draw(commandBuffer);
  }
}
}