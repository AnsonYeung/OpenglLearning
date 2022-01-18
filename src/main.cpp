#include "OpenglLearning.h"
#pragma warning(push)
#pragma warning(disable: 4005)
#include <spdlog/spdlog.h>
#pragma warning(pop)
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

int main() {
    spdlog::set_level(spdlog::level::debug);
    spdlog::info("Initializing and creating GLFW Window");

    if (!glfwInit()) {
        spdlog::critical("Failed to initialize GLFW");
        return 1;
    }

    opengllearning::App().run();
    
    spdlog::info("Terminating");
    glfwTerminate();

    return 0;
}