#pragma once

#include <vector>
#include "single_thread_system.hpp"
#include "rotation_system.hpp"
#include "../core.hpp"

namespace dud {
    struct SystemsContainer {
        std::vector<Ref<SingleThreadSystem>> systems {
                MakeRef<RotationSystem>(),
        };

        void OnUpdate(entt::registry &registry){
            for(const auto& system : systems){
                system->OnUpdate(registry);
            }
        }
    };

} // dud
