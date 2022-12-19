#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

namespace dud {
    class Camera {
    private:
        glm::mat4 projectionMatrix{1.f};
    public:
        const glm::mat4& GetProjection() const { return projectionMatrix; }

        void SetOrthographicProjection(float left, float right, float top, float bottom, float near, float far);

        void SetPerspectiveProjection(float fovy, float aspect, float near, float far);
    };
} // dud
