#include "App.h"
#include "Texture2D.h"
#include <spdlog/spdlog.h>
#include <array>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace opengllearning {

    WindowWrapper App::initWindow() {

        WindowWrapper window(defaultWidth, defaultHeight, "Learn OpenGL", nullptr, nullptr);

        if (!window) {
            spdlog::critical("Error during creation of GLFW window, terminating");
            glfwTerminate();
            exit(1);
        }

        spdlog::info("Created GLFW Window");

        window.makeContextCurrent();

        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
            spdlog::critical("Failed to initialize GLAD");
            glfwTerminate();
            exit(1);
        }

        glViewport(0, 0, defaultWidth, defaultHeight);

        return window;

    }
    
    ShaderProgram App::initShader() {

        // shader program are run in the gpu graphics pipeline
        return { "res/shader/vertexshader.vert", "res/shader/fragmentshader.frag" };

    }

    App::App(): m_window(initWindow()), m_program(initShader()), m_camera(glm::radians(45.0f), (float)defaultWidth / defaultHeight, 0, 0, 3, 0, 0) {
        if (currentApp) {
            spdlog::critical("Only one app can be active in a thread at a time! Terminating.");
            glfwTerminate();
            exit(1);
        }
        currentApp = this;
    }

    App::~App() {
        currentApp = nullptr;
    }

    void App::run() {

        glfwSetInputMode(m_window.glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        // set the event handlers
        m_window.setFramebufferSizeCallback(onFramebufferResize);
        m_window.setKeyCallback(onKeyEvent);
        m_window.setCursorPosCallback(onCursorMove);

        // load the textures
        Texture2D tex0(GL_TEXTURE0, "res/textures/container.jpg");
        Texture2D tex1(GL_TEXTURE1, "res/textures/awesomeface.png");

        if (!tex0 || !tex1) {
            spdlog::critical("Failed to load texture");
            glfwTerminate();
            exit(1);
        }

        // set the textures
        m_program.setUniform("ourTexture0", 0);
        m_program.setUniform("ourTexture1", 1);

        // now we need to feed input to our shader program
        // store the vertices in the array buffer, these will be our actual input to the shader
        // initialize 8 vertices here
        float vertices[] = {
            -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            
            // extra vertexes for textures, it's impossible to have correct texture on top and bottom face otherwise
            // ...
        };

        GLuint vbo;
        glGenBuffers(1, &vbo);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // vertex array objects are needed to store the vertex attrib arrays
        GLuint vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        // in "aPos"
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);

        // in "aColor"
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // in "aTexCoord"
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        // using element buffer object allow us to reuse vertices, 
        unsigned int indices[] = {
            0, 1, 2,
            1, 2, 4,
            1, 4, 5,
            4, 5, 7,
            3, 5, 6,
            5, 6, 7,
            0, 2, 3,
            2, 3, 6,
            0, 1, 3,
            1, 3, 5,
            2, 4, 6,
            4, 6, 7,
        };

        GLuint ebo;
        glGenBuffers(1, &ebo);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        m_numVertex = sizeof(indices) / sizeof(indices[0]);

        // color used when glClear is called on the color buffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        // wireframe mode
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        // enable depth test
        glEnable(GL_DEPTH_TEST);

        while (!m_window.shouldClose()) {

            draw();

            // will wait until at least one event occurs
            // glfwWaitEvents();

            // we need to use this so that our animation actually animates
            glfwPollEvents();

        }

    }

    void App::onFramebufferResize(GLFWwindow *window, int width, int height) {
        // should we switch context or not?
        // we might need a global "context" variable for that?
        // just do a single screen since we don't actually will initialize more than one
        App &app = *currentApp;
        glViewport(0, 0, width, height);
        app.m_windowWidth = width;
        app.m_windowHeight = height;
        app.m_camera.setWindowRatio((float)app.m_windowWidth / app.m_windowHeight);
        app.draw();
    }

    void App::onKeyEvent(GLFWwindow *window, int key, int scancode, int action, int mods) {
        App &app = *currentApp;
        if (action == GLFW_PRESS) {
            switch (key) {
            case GLFW_KEY_ESCAPE:
                app.m_window.setShouldClose(true);
                break;
            case GLFW_KEY_H:
                app.m_normalizeFlag = !app.m_normalizeFlag;
                app.m_program.setUniform("normalizeFlag", app.m_normalizeFlag);
                break;
            }
        }
        app.draw();
    }

    void App::onCursorMove(GLFWwindow *window, double xpos, double ypos) {
        static double prevX = xpos;
        static double prevY = ypos;
        constexpr double cameraSpeed = glm::radians(0.1f);
        App &app = *currentApp;
        app.m_camera.changeAngleClamped(static_cast<float>(-(ypos - prevY) * cameraSpeed), static_cast<float>(-(xpos - prevX) * cameraSpeed));
        prevX = xpos;
        prevY = ypos;
    }

    void App::processFrameInput() {
        constexpr float movementSpeed = 5.0f;
        static float lastTime{ (float)glfwGetTime() };
        float deltaTime = (float)glfwGetTime() - lastTime;
        lastTime += deltaTime;
        float moveDist = deltaTime * movementSpeed;
        // spdlog::debug("frame delta: {}s = fps: {}, moveDist: {}", deltaTime, 1 / deltaTime, moveDist);
        if (m_window.getKey(GLFW_KEY_UP) || m_window.getKey(GLFW_KEY_W)) {
            m_camera.moveWithYawOnly(0.0f, 0.0f, -moveDist);
        }
        if (m_window.getKey(GLFW_KEY_DOWN) || m_window.getKey(GLFW_KEY_S)) {
            m_camera.moveWithYawOnly(0.0f, 0.0f, moveDist);
        }
        if (m_window.getKey(GLFW_KEY_LEFT) || m_window.getKey(GLFW_KEY_A)) {
            m_camera.moveWithYawOnly(-moveDist, 0.0f, 0.0f);
        }
        if (m_window.getKey(GLFW_KEY_RIGHT) || m_window.getKey(GLFW_KEY_D)) {
            m_camera.moveWithYawOnly(moveDist, 0.0f, 0.0f);
        }
        if (m_window.getKey(GLFW_KEY_SPACE)) {
            m_camera.moveWithYawOnly(0.0f, moveDist, 0.0f);
        }
        if (m_window.getKey(GLFW_KEY_LEFT_SHIFT)) {
            m_camera.moveWithYawOnly(0.0f, -moveDist, 0.0f);
        }
    }

    void App::draw() {

        processFrameInput();

        static const std::array cubePositions{
            glm::vec3(0.0f,  0.0f,  0.0f),
            glm::vec3(2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3(2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3(1.3f, -2.0f, -2.5f),
            glm::vec3(1.5f,  2.0f, -2.5f),
            glm::vec3(1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
        };


        // Clear the buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float time{ static_cast<float>(glfwGetTime()) };
        glm::mat4 transform = m_camera.getTransformMatrix();

        for (auto &pos : cubePositions) {

            glm::mat4 modelMat(1.0f);

            modelMat = glm::translate(modelMat, pos);
            modelMat = glm::rotate(modelMat, glm::radians(time * 10), glm::vec3(1.0f, 0.3f, 0.5f));

            m_program.setUniformMatrix4fv("transform", 1, GL_FALSE, glm::value_ptr(transform * modelMat));

            // Draw directly
            //glDrawArrays(GL_TRIANGLES, 0, 3);

            // Draw using the current element buffer object
            glDrawElements(GL_TRIANGLES, m_numVertex, GL_UNSIGNED_INT, nullptr);
        }

        m_window.swapBuffers();

    }

} // opengllearning
