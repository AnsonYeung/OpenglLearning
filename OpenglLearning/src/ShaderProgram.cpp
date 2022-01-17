#include "ShaderProgram.h"
namespace opengllearning {

	ShaderProgram::ShaderProgram(const Shader &vert, const Shader &frag)
        :id(glCreateProgram()){

        glAttachShader(id, vert.id);
        glAttachShader(id, frag.id);
        glLinkProgram(id);
        glUseProgram(id);

	}

    ShaderProgram::~ShaderProgram() {
        glDeleteProgram(id);
    }

    void ShaderProgram::setUniform(const std::string &name, GLint v0) {
        glUniform1i(getUniformLoc(name), v0);
    }

    void ShaderProgram::setUniform(const std::string &name, GLfloat v0, GLfloat v1, GLfloat v2) {
        glUniform3f(getUniformLoc(name), v0, v1, v2);
    }

    void ShaderProgram::setUniformMatrix4fv(const std::string &name, GLsizei count, GLboolean transpose, const GLfloat *value) {
        glUniformMatrix4fv(getUniformLoc(name), count, transpose, value);
    }


    GLuint ShaderProgram::getUniformLoc(const std::string &name) {

        auto cacheIt = m_uniformCache.find(name);
        if (cacheIt != m_uniformCache.end()) {
            return cacheIt->second;
        }
        
        // cache miss
        GLuint loc = glGetUniformLocation(id, name.c_str());
        m_uniformCache[name] = loc;
        return loc;

    }

}