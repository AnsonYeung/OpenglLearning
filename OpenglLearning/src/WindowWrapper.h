#pragma once
#include "base.h"
namespace opengllearning {
    class WindowWrapper {
    public:
        WindowWrapper(int width, int height, const char *title, GLFWmonitor *monitor, GLFWwindow *share);
        WindowWrapper(const WindowWrapper &) = delete;
        ~WindowWrapper();
        operator bool();
        GLFWwindow *get_ptr();
    private:
        GLFWwindow *m_window;
    };
}