#pragma once
#include "base.h"
#include "WindowWrapper.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include <unordered_map>
#include <glm/glm.hpp>

namespace opengllearning {
    class App {
    public:
        App();
        App(const App &) = delete;
        ~App();
        void run();
    private:

        static constexpr GLsizei defaultWidth = 1024;
        static constexpr GLsizei defaultHeight = 768;
        inline static App *currentApp = nullptr;

        WindowWrapper m_window;
        ShaderProgram m_program;
        GLsizei m_windowWidth = defaultWidth;
        GLsizei m_windowHeight = defaultHeight;
        bool m_normalizeFlag = false;
        GLsizei m_numVertex = 0;
        Camera m_camera;

        static WindowWrapper initWindow();
        static ShaderProgram initShader();
        static void onFramebufferResize(GLFWwindow *window, int width, int height);
        static void onKeyEvent(GLFWwindow *window, int key, int scancode, int action, int mods);
        static void onCursorMove(GLFWwindow *window, double xpos, double ypos);

        void processFrameInput();
        void draw();

    };
}
