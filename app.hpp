#pragma once

#include "window.hpp"
#include "mesh.hpp"
#include "core.hpp"
#include "scene.hpp"
#include "renderer.hpp"
#include "render_system.hpp"
#include "systems/dud_systems_container.hpp"

namespace dud {
class App {
 public:
  static constexpr int width = 800;
  static constexpr int height = 800;

  App();
  ~App();
  App(const App &) = delete;
  App &operator=(const App &) = delete;

  void Run();
 private:
  void LoadScene();
  void Render(const RenderSystem &renderSystem);

  Window window{width, height, "Main Window"};
  Device device{window};
  Renderer renderer{window, device};
  SystemsContainer systemContainer{};

  Scope<Scene> scene;
};
}