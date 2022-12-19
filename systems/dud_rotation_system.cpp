#include "dud_rotation_system.hpp"
#include "../components/dud_transform_component.hpp"
#include "../components/dud_mesh_component.hpp"

void dud::RotationSystem::OnUpdate(entt::registry &registry) {
    auto view = registry.view<TransformComponent, MeshComponent>();

    for (auto [entity, transform, mesh] : view.each()) {
        transform.rotation.x += 0.0001f;
        transform.rotation.y += 0.0001f;
        transform.rotation.z += 0.0001f;
    }
}