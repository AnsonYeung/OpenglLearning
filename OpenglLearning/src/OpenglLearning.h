#pragma once
#include "base.h"
#include "WindowWrapper.h"
#include "ShaderProgram.h"
namespace opengllearning {
	class App {
	public:
		App() : window(initWindow()), program(initShader()) {}
		void run();
	private:
		WindowWrapper window;
		ShaderProgram program;
		static WindowWrapper initWindow();
		static ShaderProgram initShader();
		static void on_framebuffer_resize(GLFWwindow *window, int width, int height);
		void draw();
	};
}