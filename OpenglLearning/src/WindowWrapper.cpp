#include "WindowWrapper.h"
#pragma warning(push)
#pragma warning(disable: 4005)
#include <spdlog/spdlog.h>
#pragma warning(pop)
namespace opengllearning {
    WindowWrapper::WindowWrapper(int width, int height, const char *title, GLFWmonitor *monitor, GLFWwindow *share)
        : m_window(makeWindow(width, height, title, monitor, share)) {

        spdlog::debug("Made window {}", fmt::ptr(m_window));
        if (!m_window) {
            spdlog::critical("Failed to create GLFW window");
        }

    }

    WindowWrapper::~WindowWrapper() {
        if (m_window) {
            glfwDestroyWindow(m_window);
            spdlog::debug("Destroyed window {}", fmt::ptr(m_window));
        }
    }

    WindowWrapper::WindowWrapper(WindowWrapper &&orig) noexcept: m_window(orig.m_window) {
        orig.m_window = nullptr;
    }

    void WindowWrapper::makeContextCurrent() {
        glfwMakeContextCurrent(m_window);
    }

    void WindowWrapper::swapBuffers() {
        glfwSwapBuffers(m_window);
    }

    void WindowWrapper::setFramebufferSizeCallback(GLFWframebuffersizefun callback) {
        glfwSetFramebufferSizeCallback(m_window, callback);
    }

    bool WindowWrapper::shouldClose() {
        return glfwWindowShouldClose(m_window);
    }

    void WindowWrapper::setShouldClose(bool value) {
        glfwSetWindowShouldClose(m_window, value);
    }

    int WindowWrapper::getKey(int key) {
        return glfwGetKey(m_window, key);
    }

    WindowWrapper::operator bool() {
        return m_window;
    }

    GLFWwindow *WindowWrapper::makeWindow(int width, int height, const char *title, GLFWmonitor *monitor, GLFWwindow *share) {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        return glfwCreateWindow(width, height, title, monitor, share);
    }

}