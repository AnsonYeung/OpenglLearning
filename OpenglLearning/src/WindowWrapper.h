#pragma once
#include "base.h"
namespace opengllearning {
    class WindowWrapper {
    public:
        GLFWwindow *const window;
        WindowWrapper(int width, int height, const char *title, GLFWmonitor *monitor, GLFWwindow *share);
        WindowWrapper(const WindowWrapper &) = delete;
        WindowWrapper(WindowWrapper &&) noexcept;
        ~WindowWrapper();
        void makeContextCurrent();
        void swapBuffers();
        void setFramebufferSizeCallback(GLFWframebuffersizefun callback);
        bool shouldClose();
        void setShouldClose(bool value);
        int getKey(int key);
        operator bool();
    private:
        bool good = true;
        static GLFWwindow *makeWindow(int width, int height, const char *title, GLFWmonitor *monitor, GLFWwindow *share);
    };
}