#pragma once

#include <vector>
#include "dud_single_thread_system.hpp"
#include "dud_rotation_system.hpp"
#include "../dud_core.hpp"

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
