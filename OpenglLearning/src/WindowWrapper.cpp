#include "WindowWrapper.h"
#pragma warning(push)
#pragma warning(disable: 4005)
#include <spdlog/spdlog.h>
#pragma warning(pop)
namespace opengllearning {
    WindowWrapper::WindowWrapper(int width, int height, const char *title, GLFWmonitor *monitor, GLFWwindow *share) {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_window = glfwCreateWindow(width, height, title, monitor, share);

        if (!m_window) {
            // spdlog::critical("Failed to create GLFW window");
        }
    }

    WindowWrapper::~WindowWrapper() {
        if (!m_window) {
            glfwDestroyWindow(m_window);
        }
    }

    WindowWrapper::operator bool() {
        return static_cast<bool>(m_window);
    }

    GLFWwindow *WindowWrapper::get_ptr() {
        return m_window;
    }
}