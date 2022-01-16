#pragma once
#include "base.h"
#include <string_view>
namespace opengllearning {
	class Shader {
	public:
		Shader(std::string_view filename, GLenum type);
		Shader(const Shader &) = delete;
		~Shader();
		operator bool();
		GLuint getId();
	private:
		GLuint m_shaderId;
	};
}