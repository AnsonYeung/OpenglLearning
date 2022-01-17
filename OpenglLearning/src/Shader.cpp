#include "Shader.h"
#include <fstream>
#include <sstream>
#pragma warning(push)
#pragma warning(disable: 4005)
#include <spdlog/spdlog.h>
#pragma warning(pop)

namespace opengllearning {

	Shader::Shader(const char *filename, GLenum type): id(glCreateShader(type)) {

		if (!id) {
			spdlog::critical("Failed to create shader");
			good = false;
			return;
		}

		std::ifstream shaderFile{ filename };
		if (!shaderFile) {
			spdlog::critical("Failed to open shader file \"{}\"", filename);
			good = false;
			return;
		}

		std::ostringstream buf;
		buf << shaderFile.rdbuf();

		const std::string s = buf.str();
		const char *shaderSource = s.c_str();

		glShaderSource(id, 1, &shaderSource, nullptr);
		glCompileShader(id);

		GLint compileStatus;
		glGetShaderiv(id, GL_COMPILE_STATUS, &compileStatus);

		if (!compileStatus) {
			char infoLog[256];
			glGetShaderInfoLog(id, 256, NULL, infoLog);
			spdlog::critical("Failed to compile shader file \"{}\", info log:\n{}", filename, infoLog);
			good = false;
			return;
		}

	}

	Shader::~Shader() {
		if (id)
			glDeleteShader(id);
	}

	Shader::operator bool() {
		return good;
	}

} // opengllearning