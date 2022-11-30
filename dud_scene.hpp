#pragma once

#include "entt.hpp"
#include "dud_device.hpp"

namespace dud {

    class Scene {
    public:
        entt::registry registry;
    private:
        Device& device;
    public:
        Scene(dud::Device &device);
        ~Scene();
    };

} // dud
