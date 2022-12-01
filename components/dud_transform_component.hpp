#pragma once

#include "glm/glm.hpp"

namespace dud {

    struct TransformComponent
    {
        glm::mat4 Transform;

        TransformComponent() = default;
        TransformComponent(const TransformComponent&) = default;
        TransformComponent(const glm::mat4& transform) : Transform(transform){}

        operator const glm::mat4& () const { return Transform; }
        operator const glm::mat4& () { return Transform; }
    };
} // dud