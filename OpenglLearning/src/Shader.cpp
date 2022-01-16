#include "Shader.h"
#include <fstream>
#include <sstream>
#pragma warning(push)
#pragma warning(disable: 4005)
#include <spdlog/spdlog.h>
#pragma warning(pop)

namespace opengllearning {

Shader::Shader(std::string_view filename, GLenum type) {

	m_shaderId = glCreateShader(type);
	if (!m_shaderId) {
		spdlog::critical("Failed to create shader");
		return;
	}

	std::ifstream shaderFile{ std::string(filename) };
	if (!shaderFile) {
		spdlog::critical("Failed to open shader file {}", filename);
		glDeleteShader(m_shaderId);
		m_shaderId = 0;
		return;
	}

	std::stringstream buf;
	buf << shaderFile.rdbuf();

	const std::string s = buf.str();
	const char *shaderSource = s.c_str();

	glShaderSource(m_shaderId, 1, &shaderSource, nullptr);
	glCompileShader(m_shaderId);

	GLint compileStatus;
	glGetShaderiv(m_shaderId, GL_COMPILE_STATUS, &compileStatus);

	if (!compileStatus) {
		char infoLog[256];
		glGetShaderInfoLog(m_shaderId, 256, NULL, infoLog);
		spdlog::critical("Failed to compile shader, file path = {}", filename);
		spdlog::critical("{}", infoLog);
		glDeleteShader(m_shaderId);
		m_shaderId = 0;
	}

}

Shader::~Shader() {
	if (!m_shaderId)
		glDeleteShader(m_shaderId);
}

Shader::operator bool() {
	return static_cast<bool>(m_shaderId);
}

GLuint Shader::getId() {
	return m_shaderId;
}

} // opengllearning