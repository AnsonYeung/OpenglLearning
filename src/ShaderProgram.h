#pragma once
#include "base.h"
#include "Shader.h"
#include <unordered_map>
namespace opengllearning {
	class ShaderProgram {
	public:
		const GLuint &id = m_id;
		ShaderProgram(const Shader &vert, const Shader &frag);
		ShaderProgram(const char *vertFile, const char *fragFile)
			: ShaderProgram(Shader(vertFile, GL_VERTEX_SHADER), Shader(fragFile, GL_FRAGMENT_SHADER)) {}
		ShaderProgram(const ShaderProgram &) = delete;
		~ShaderProgram();
		void setUniform(const std::string &name, GLint v0);
		void setUniform(const std::string &name, GLfloat v0, GLfloat v1, GLfloat v2);
		void setUniformMatrix4fv(const std::string &name, GLsizei count, GLboolean transpose, const GLfloat *value);
	private:
		GLuint m_id;
		std::unordered_map<std::string, GLuint> m_uniformCache;
		GLuint getUniformLoc(const std::string &name);
	};
}