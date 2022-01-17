#include "WindowWrapper.h"
#pragma warning(push)
#pragma warning(disable: 4005)
#include <spdlog/spdlog.h>
#pragma warning(pop)
namespace opengllearning {
    WindowWrapper::WindowWrapper(int width, int height, const char *title, GLFWmonitor *monitor, GLFWwindow *share)
        : window(makeWindow(width, height, title, monitor, share)) {

        spdlog::debug("Made window {}", fmt::ptr(window));
        if (!window) {
            spdlog::critical("Failed to create GLFW window");
        }

    }

    WindowWrapper::~WindowWrapper() {
        if (window && good) {
            glfwDestroyWindow(window);
            spdlog::debug("Destroyed window {}", fmt::ptr(window));
        }
    }

    WindowWrapper::WindowWrapper(WindowWrapper &&orig) noexcept: window(orig.window) {
        orig.good = false;
    }

    void WindowWrapper::makeContextCurrent() {
        glfwMakeContextCurrent(window);
    }

    void WindowWrapper::swapBuffers() {
        glfwSwapBuffers(window);
    }

    void WindowWrapper::setFramebufferSizeCallback(GLFWframebuffersizefun callback) {
        glfwSetFramebufferSizeCallback(window, callback);
    }

    bool WindowWrapper::shouldClose() {
        return glfwWindowShouldClose(window);
    }

    void WindowWrapper::setShouldClose(bool value) {
        glfwSetWindowShouldClose(window, value);
    }

    int WindowWrapper::getKey(int key) {
        return glfwGetKey(window, key);
    }

    WindowWrapper::operator bool() {
        return window;
    }

    GLFWwindow *WindowWrapper::makeWindow(int width, int height, const char *title, GLFWmonitor *monitor, GLFWwindow *share) {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        return glfwCreateWindow(width, height, title, monitor, share);
    }

}