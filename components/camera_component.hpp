#pragma once

#include <glm/glm.hpp>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

namespace dud {
struct CameraComponent {
 private:
  glm::mat4 projectionMatrix{1.f};
  glm::mat4 viewMatrix{1.f};
 public:
  CameraComponent() = default;

  CameraComponent(const CameraComponent &) = default;

  const glm::mat4 &GetProjection() const { return projectionMatrix; }

  const glm::mat4 &GetView() const { return viewMatrix; }

  glm::mat4 GetProjectionView() const { return GetView() * GetProjection(); }

  void SetOrthographicProjection(float left,
								 float right,
								 float top,
								 float bottom,
								 float near,
								 float far);

  void SetPerspectiveProjection(float fovy,
								float aspect,
								float near,
								float far);

  void SetViewDirection(glm::vec3 position,
						glm::vec3 direction,
						glm::vec3 up = glm::vec3(0.f, -1.f, 0.f));

  void SetViewTarget(glm::vec3 position,
					 glm::vec3 target,
					 glm::vec3 up = glm::vec3(0.f, -1.f, 0.f));

  void SetViewYXZ(glm::vec3 position, glm::vec3 rotation);
};
} // dud
