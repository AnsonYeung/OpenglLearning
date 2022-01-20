#include "App.h"
#include <spdlog/spdlog.h>
#include <filesystem>
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

int main() {
    spdlog::set_level(spdlog::level::debug);
    spdlog::debug("Current working directory is {}", std::filesystem::current_path().string());
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
