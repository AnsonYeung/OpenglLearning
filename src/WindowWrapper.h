#pragma once
#include "base.h"
namespace opengllearning {
    class WindowWrapper {
    public:
        GLFWwindow *const &glfwWindow = m_window;
        WindowWrapper(int width, int height, const char *title, GLFWmonitor *monitor, GLFWwindow *share);
        WindowWrapper(const WindowWrapper &) = delete;
        WindowWrapper(WindowWrapper &&) noexcept;
        ~WindowWrapper();
        void makeContextCurrent();
        void swapBuffers();
        void setFramebufferSizeCallback(GLFWframebuffersizefun callback);
        void setKeyCallback(GLFWkeyfun callback);
        void setCursorPosCallback(GLFWcursorposfun callback);
        bool shouldClose();
        void setShouldClose(bool value);
        int getKey(int key);
        operator bool();
    private:
        GLFWwindow *m_window;
        static GLFWwindow *makeWindow(int width, int height, const char *title, GLFWmonitor *monitor, GLFWwindow *share);
    };
}
