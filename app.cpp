#include "app.hpp"
#include "macros.hpp"

//std
#include "chrono"

namespace dud {
void App::Run() {
  RenderSystem renderSystem{device, renderer.GetSwapChainRenderPass()};

  auto currentTime = std::chrono::high_resolution_clock::now();

  while (!window.ShouldClose()) {
	glfwPollEvents();

	auto newTime = std::chrono::high_resolution_clock::now();
	float frameTime = std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
	currentTime = newTime;

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