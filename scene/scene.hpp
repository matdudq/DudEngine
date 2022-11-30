#pragma once

#include "entt.hpp"

namespace dud {

    class Scene {
    private:
        entt::registry registry;
    public:
        Scene();
        ~Scene();
    };

} // dud
