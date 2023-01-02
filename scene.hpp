#pragma once

#include "device.hpp"
#include "components/dud_camera_component.hpp"

#include <iostream>

#include "entt.hpp"

namespace dud {

class Scene {
 public:
  entt::registry registry;
 private:
  Device &device;
 public:
  Scene(dud::Device &device);
  ~Scene();

  CameraComponent *GetPrimaryCamera() {
	auto cameraView = registry.view<CameraComponent>();
	for (auto [entity, camera] : cameraView.each()) {
	  return &camera;
	}

	std::cerr << "There is no camera in the scene!" << std::endl;
	return nullptr;
  }
};
}
