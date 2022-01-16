#include "WindowWrapper.h"
#include "OpenglLearning.h"
#include "Shader.h"
#pragma warning(push)
#pragma warning(disable: 4005)
#include <spdlog/spdlog.h>
#pragma warning(pop)
namespace opengllearning {
namespace app {

    inline GLFWwindow *window;

    void draw();

    void run() {
        opengllearning::WindowWrapper window_obj(800, 600, "Learn OpenGL", nullptr, nullptr);

        if (!window_obj) {
            spdlog::critical("Failed to create GLFW window");
            glfwTerminate();
            exit(1);
        }

        spdlog::info("Created GLFW Window");

        window = window_obj.get_ptr();
        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
            spdlog::critical("Failed to initialize GLAD");
            glfwTerminate();
            exit(1);
        }

        glViewport(0, 0, 800, 600);
        glfwSetFramebufferSizeCallback(window, on_framebuffer_resize);

        float vertices[] = {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
        };

        GLuint vbo;
        glGenBuffers(1, &vbo);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        opengllearning::Shader vertexShader("res/shader/vertexshader.vert", GL_VERTEX_SHADER);
        opengllearning::Shader fragmentShader("res/shader/fragmentshader.frag", GL_FRAGMENT_SHADER);

        GLuint shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader.getId());
        glAttachShader(shaderProgram, fragmentShader.getId());
        glLinkProgram(shaderProgram);
        glUseProgram(shaderProgram);

        unsigned int indices[] = {
            0, 1, 3,
            0, 2, 3
        };

        GLuint vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        // "aPos" which is passed to the vertex shader
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);

        // "aColor" which is passed to the vertex shader
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        GLuint ebo;
        glGenBuffers(1, &ebo);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        bool normalizeFlag = false;
        GLint nFlagLoc = glGetUniformLocation(shaderProgram, "normalizeFlag");

        while (!glfwWindowShouldClose(window)) {

            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
                glfwSetWindowShouldClose(window, true);
            }

            if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
                normalizeFlag = !normalizeFlag;
                glUniform1i(nFlagLoc, normalizeFlag);
            }

            draw();

            glfwWaitEvents();
            //spdlog::info("Event received");
        }
    }

    void on_framebuffer_resize(GLFWwindow *window, int width, int height) {
        glViewport(0, 0, width, height);
        draw();
    }

    void draw() {
        // Draw directly
        //glDrawArrays(GL_TRIANGLES, 0, 3);

        // Draw from the current element buffer object
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        glfwSwapBuffers(window);
    }

} // app
} // opengllearning