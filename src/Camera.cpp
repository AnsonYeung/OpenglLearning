#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
namespace opengllearning {
	Camera::Camera(float fov, float windowRatio, float x, float y, float z, float pitch, float yaw)
		: m_fov(fov), m_windowRatio(windowRatio), m_x(x), m_y(x), m_z(z), m_pitch(pitch), m_yaw(yaw) {

		recalculate();

	}

	glm::mat4 Camera::getTransformMatrix() {
		return m_transformMatrix;
	}

	void Camera::moveWithYawOnly(float deltaX, float deltaY, float deltaZ) {
		m_x += deltaX * glm::cos(m_yaw) + deltaZ * glm::sin(m_yaw);
		m_y += deltaY;
		m_z += deltaZ * glm::cos(m_yaw) - deltaX * glm::sin(m_yaw);
		recalculate();
	}

	void Camera::changeAngleClamped(float deltaPitch, float deltaYaw) {
		m_pitch += deltaPitch;
		m_yaw += deltaYaw;
		m_pitch = glm::clamp(m_pitch, -glm::half_pi<float>(), glm::half_pi<float>());
		recalculate();
	}
	void Camera::setFov(float fov) {
		m_fov = fov;
		recalculate();
	}

	void Camera::setWindowRatio(float windowRatio) {
		m_windowRatio = windowRatio;
		recalculate();
	}

	void Camera::recalculate() {
		// finally, multiply by the projection matrix
		m_transformMatrix = glm::perspective(m_fov, m_windowRatio, nearDist, farDist);

		// then rotate with pitch
		m_transformMatrix = glm::rotate(m_transformMatrix, m_pitch, glm::vec3(-1.0f, 0.0f, 0.0f));

		// then rotate with yaw
		m_transformMatrix = glm::rotate(m_transformMatrix, m_yaw, glm::vec3(0.0f, -1.0f, 0.0f));

		// first translate
		m_transformMatrix = glm::translate(m_transformMatrix, glm::vec3(-m_x, -m_y, -m_z));

	}
}
