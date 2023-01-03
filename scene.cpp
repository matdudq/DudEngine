#include "scene.hpp"
#include "components/transform_component.hpp"
#include "components/mesh_component.hpp"

namespace dud {
Scene::Scene(Device &device) : device(device) {
  //Hardcoded scene

  //Object 1
  Mesh::ModelBuilder modelBuilder{};
  modelBuilder.vertices = {
	  // left face (white)
	  {{-.5f, -.5f, -.5f}, {.9f, .9f, .9f}},
	  {{-.5f, .5f, .5f}, {.9f, .9f, .9f}},
	  {{-.5f, -.5f, .5f}, {.9f, .9f, .9f}},
	  {{-.5f, .5f, -.5f}, {.9f, .9f, .9f}},

	  // right face (yellow)
	  {{.5f, -.5f, -.5f}, {.8f, .8f, .1f}},
	  {{.5f, .5f, .5f}, {.8f, .8f, .1f}},
	  {{.5f, -.5f, .5f}, {.8f, .8f, .1f}},
	  {{.5f, .5f, -.5f}, {.8f, .8f, .1f}},

	  // top face (orange, remember y axis points down)
	  {{-.5f, -.5f, -.5f}, {.9f, .6f, .1f}},
	  {{.5f, -.5f, .5f}, {.9f, .6f, .1f}},
	  {{-.5f, -.5f, .5f}, {.9f, .6f, .1f}},
	  {{.5f, -.5f, -.5f}, {.9f, .6f, .1f}},

	  // bottom face (red)
	  {{-.5f, .5f, -.5f}, {.8f, .1f, .1f}},
	  {{.5f, .5f, .5f}, {.8f, .1f, .1f}},
	  {{-.5f, .5f, .5f}, {.8f, .1f, .1f}},
	  {{.5f, .5f, -.5f}, {.8f, .1f, .1f}},

	  // nose face (blue)
	  {{-.5f, -.5f, 0.5f}, {.1f, .1f, .8f}},
	  {{.5f, .5f, 0.5f}, {.1f, .1f, .8f}},
	  {{-.5f, .5f, 0.5f}, {.1f, .1f, .8f}},
	  {{.5f, -.5f, 0.5f}, {.1f, .1f, .8f}},

	  // tail face (green)
	  {{-.5f, -.5f, -0.5f}, {.1f, .8f, .1f}},
	  {{.5f, .5f, -0.5f}, {.1f, .8f, .1f}},
	  {{-.5f, .5f, -0.5f}, {.1f, .8f, .1f}},
	  {{.5f, -.5f, -0.5f}, {.1f, .8f, .1f}},
  };

  modelBuilder.indices = {0,  1,  2,  0,  3,  1,  4,  5,  6,  4,  7,  5,  8,  9,  10, 8,  11, 9,
						  12, 13, 14, 12, 15, 13, 16, 17, 18, 16, 19, 17, 20, 21, 22, 20, 23, 21};

  auto entity = registry.create();

  registry.emplace<TransformComponent>(entity,
									   glm::vec3(0.0f, 0.0f, 3.5f),
									   glm::vec3(1.0f),
									   glm::vec3(0.0f));
  registry.emplace<MeshComponent>(entity,
								  std::make_unique<Mesh>(device, modelBuilder),
								  glm::vec4{0.1f, 0.8f, 0.5f, 1.0f});

  auto cameraEntity = registry.create();
  registry.emplace<CameraComponent>(cameraEntity);
}

Scene::~Scene() {

}

} // dud