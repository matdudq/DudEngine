#pragma once

#include "single_thread_system.hpp"

namespace dud{
    struct RotationSystem : SingleThreadSystem {
        void OnUpdate(entt::registry &registry) override;
    };
}
