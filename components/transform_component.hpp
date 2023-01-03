#pragma once

#include "glm/glm.hpp"

namespace dud {

struct TransformComponent {
  glm::vec3 translation{};
  glm::vec3 scale{};
  glm::vec3 rotation{};

  TransformComponent() = default;
  TransformComponent(const TransformComponent &) = default;
  TransformComponent(const glm::vec3 &translation,
					 const glm::vec3 &scale,
					 const glm::vec3 &rotation)
	  : translation(translation), scale(scale), rotation(rotation) {}

  operator glm::mat4() const { return GetTransform(); }

  glm::mat4 GetTransform() const;
};
} // dud
