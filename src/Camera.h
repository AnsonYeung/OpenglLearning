#pragma once
#include "WindowWrapper.h"
#include <glm/glm.hpp>
namespace opengllearning {
    class Camera {
    public:
        Camera(float fov, float windowRatio, float x, float y, float z, float pitch, float yaw);
        glm::mat4 getTransformMatrix();
        void moveWithYawOnly(float deltaX, float deltaY, float deltaZ);
        void changeAngleClamped(float deltaPitch, float deltaYaw);
        void setFov(float fov);
        void setWindowRatio(float windowRatio);
    private:
        constexpr static float nearDist = 0.1f;
        constexpr static float farDist = 100.0f;
        float m_x, m_y, m_z;
        float m_pitch, m_yaw;
        float m_fov, m_windowRatio;
        glm::mat4 m_transformMatrix;
        void recalculate();
    };
}
