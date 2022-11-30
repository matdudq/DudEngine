#include "scene.hpp"
#include "glm/glm.hpp"

namespace dud {
    Scene::Scene() {
        struct TransformComponent
        {
            glm::mat4 Transform;

            TransformComponent() = default;
            TransformComponent(const TransformComponent&) = default;
            TransformComponent(const glm::mat4& transform) : Transform(transform){}

            operator const glm::mat4& () const { return Transform; }
            operator const glm::mat4& () { return Transform; }
        };

        entt::entity entity = registry.create();
        registry.emplace<TransformComponent>(entity, glm::mat4(1.0f));
    }

    Scene::~Scene() {

    }
} // dud