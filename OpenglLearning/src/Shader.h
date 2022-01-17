#pragma once
#include "base.h"
#include <string_view>
namespace opengllearning {
	class Shader {
	public:
		const GLuint id;
		Shader(const char *filename, GLenum type);
		Shader(const Shader &) = delete;
		~Shader();
		operator bool();
	private:
		bool good = true;
	};
}