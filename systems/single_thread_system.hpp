#pragma once

#include "entt.hpp"

namespace dud {
    struct SingleThreadSystem {
        virtual void OnUpdate(entt::registry &registry) = 0;
    };
}
