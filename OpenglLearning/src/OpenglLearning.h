#pragma once
#include "base.h"
#include "WindowWrapper.h"
#include "ShaderProgram.h"
#include <unordered_map>

namespace opengllearning {
	class App {
	public:
		App();
		~App();
		void run();
		static App &getAppByWindow(GLFWwindow *window);
	private:
		WindowWrapper window;
		ShaderProgram program;
		inline static std::unordered_map<GLFWwindow *, App *> windowAppMap{};
		static WindowWrapper initWindow();
		static ShaderProgram initShader();
		static void on_framebuffer_resize(GLFWwindow *window, int width, int height);
		void draw();
	};
}