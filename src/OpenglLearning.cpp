#include "OpenglLearning.h"
#include "Texture2D.h"
#pragma warning(push)
#pragma warning(disable: 4005)
#include <spdlog/spdlog.h>
#pragma warning(pop)
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace opengllearning {

    WindowWrapper App::initWindow() {

        WindowWrapper window(1024, 768, "Learn OpenGL", nullptr, nullptr);

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

        glViewport(0, 0, 1024, 768);
        window.setFramebufferSizeCallback(on_framebuffer_resize);

        return window;

    }
    
    ShaderProgram App::initShader() {

        // shader program are run in the gpu graphics pipeline
        return { "res/shader/vertexshader.vert", "res/shader/fragmentshader.frag" };

    }

    App::App(): window(initWindow()), program(initShader()) {
        windowAppMap[window.glfwWindow] = this;
    }

    App::~App() {
        windowAppMap.erase(window.glfwWindow);
    }

    App &App::getAppByWindow(GLFWwindow *window) {
        return *windowAppMap[window];
    }


    void App::run() {

        // load the textures
        Texture2D tex0(GL_TEXTURE0, "res/textures/container.jpg");
        Texture2D tex1(GL_TEXTURE1, "res/textures/awesomeface.png");

        if (!tex0 || !tex1) {
            spdlog::critical("Failed to load texture");
            glfwTerminate();
            exit(1);
        }

        // set the textures
        program.setUniform("ourTexture0", 0);
        program.setUniform("ourTexture1", 1);

        // now we need to feed input to our shader program
        // store the vertices in the array buffer, these will be our actual input to the shader
        float vertices[] = {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
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

        // using element buffer object allow us to reuse vertices
        unsigned int indices[] = {
            0, 1, 3,
            0, 2, 3
        };

        GLuint ebo;
        glGenBuffers(1, &ebo);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // wireframe mode
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        bool normalizeFlag = false;
        GLfloat translation[] = { 0.0f, 0.0f, 0.0f };

        while (!window.shouldClose()) {

            if (window.getKey(GLFW_KEY_ESCAPE)) {
                window.setShouldClose(true);
            }

            if (window.getKey(GLFW_KEY_H)) {
                normalizeFlag = !normalizeFlag;
                program.setUniform("normalizeFlag", normalizeFlag);
            }

            if (window.getKey(GLFW_KEY_UP)) {
                translation[1] += 0.05f;
            }

            if (window.getKey(GLFW_KEY_DOWN)) {
                translation[1] -= 0.05f;
            }

            if (window.getKey(GLFW_KEY_LEFT)) {
                translation[0] -= 0.05f;
            }

            if (window.getKey(GLFW_KEY_RIGHT)) {
                translation[0] += 0.05f;
            }

            program.setUniform("translation", translation[0], translation[1], translation[2]);

            draw();

            // process key event only when there is event? when mouse move, the loop will run faster too (oops)
            // glfwWaitEvents();

            // we need to use this so that our animation actually animates
            glfwPollEvents();
        }
    }

    void App::on_framebuffer_resize(GLFWwindow *window, int width, int height) {
        glViewport(0, 0, width, height);
        App::getAppByWindow(window).draw();
    }

    void App::draw() {

        glm::mat4 transform(1.0f);
        transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
        transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

        program.setUniformMatrix4fv("transform", 1, GL_FALSE, glm::value_ptr(transform));

        // Clear the buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        // Draw directly
        //glDrawArrays(GL_TRIANGLES, 0, 3);

        // Draw using the current element buffer object
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        window.swapBuffers();

    }

} // opengllearning
