#include "Shader.h"
#include <fstream>
#include <sstream>
#include <spdlog/spdlog.h>

namespace opengllearning {

	Shader::Shader(const char *filename, GLenum type): m_id(glCreateShader(type)) {

		if (!m_id) {
			spdlog::critical("Failed to create shader");
			glDeleteShader(m_id);
			m_id = 0;
			return;
		}

		std::ifstream shaderFile{ filename };
		if (!shaderFile) {
			spdlog::critical("Failed to open shader file \"{}\"", filename);
			glDeleteShader(m_id);
			m_id = 0;
			return;
		}

		std::ostringstream buf;
		buf << shaderFile.rdbuf();

		const std::string s = buf.str();
		const char *shaderSource = s.c_str();

		glShaderSource(m_id, 1, &shaderSource, nullptr);
		glCompileShader(m_id);

		GLint compileStatus;
		glGetShaderiv(m_id, GL_COMPILE_STATUS, &compileStatus);

		if (!compileStatus) {
			char infoLog[256];
			glGetShaderInfoLog(m_id, 256, NULL, infoLog);
			spdlog::critical("Failed to compile shader file \"{}\", info log:\n{}", filename, infoLog);
			glDeleteShader(m_id);
			m_id = 0;
			return;
		}

		spdlog::debug("Created shader (id: {}) from file \"{}\"", m_id, filename);

	}

	Shader::~Shader() {
		if (m_id) {
			glDeleteShader(m_id);
			spdlog::debug("Deleted shader (id: {})", m_id);
		}
	}

	Shader::operator bool() {
		return m_id;
	}

} // opengllearning
