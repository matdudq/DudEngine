#pragma once

#include "../mesh.hpp"
#include "../core.hpp"

#include <utility>

namespace dud {
struct MeshComponent {
  Ref<Mesh> model;
  glm::vec4 color;

  MeshComponent() = default;
  MeshComponent(const MeshComponent &) = default;
  MeshComponent(Ref<Mesh> transform, glm::vec4 color) : model(std::move(
	  transform)), color(color) {}
};
}

