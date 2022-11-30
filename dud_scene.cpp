#include "dud_scene.hpp"
#include "components/dud_transform_component.hpp"
#include "components/dud_mesh_component.hpp"

namespace dud {
    Scene::Scene(Device &device) : device(device){
        //Hardcoded scene

        //Object 1
        std::vector<Mesh::Vertex> vertices = {
                {{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}},
                {{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}},
                {{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}},
        };
        auto entity = registry.create();
        registry.emplace<TransformComponent>(entity, glm::mat4(0.0f));
        registry.emplace<MeshComponent>(entity,
                                        std::make_unique<Mesh>(device, vertices),
                                        glm::vec4{0.1f, 0.8f, 0.1f, 1.0f});
    }

    Scene::~Scene() {

    }

} // dud