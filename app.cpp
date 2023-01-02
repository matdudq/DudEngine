#include "app.hpp"
#include "macros.hpp"

namespace dud {
void App::Run() {
  RenderSystem renderSystem{device, renderer.GetSwapChainRenderPass()};
  while (!window.ShouldClose()) {
	glfwPollEvents();
	systemContainer.OnUpdate(scene->registry);
	Render(renderSystem);
  }

  vkDeviceWaitIdle(device.GetDevice());
}

App::App() {
  LoadScene();
}

App::~App() {
}

void App::LoadScene() {
  scene = std::make_unique<Scene>(device);
}

void App::Render(const RenderSystem &renderSystem) {
  if (auto commandBuffer = renderer.BeginFrame()) {
	renderer.BeginSwapChainRenderPass(commandBuffer);
	renderSystem.RenderScene(commandBuffer, scene, renderer);
	renderer.EndSwapChainRenderPass(commandBuffer);
	renderer.EndFrame();
  }
}
}