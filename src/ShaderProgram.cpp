#include "ShaderProgram.h"
#pragma warning(push)
#pragma warning(disable: 4005)
#include <spdlog/spdlog.h>
#pragma warning(pop)
namespace opengllearning {

	ShaderProgram::ShaderProgram(const Shader &vert, const Shader &frag)
        :m_id(glCreateProgram()){

        glAttachShader(m_id, vert.id);
        glAttachShader(m_id, frag.id);
        glLinkProgram(m_id);
        glUseProgram(m_id);

        spdlog::debug("Created shader prorgram (id: {})", m_id);

	}

    ShaderProgram::~ShaderProgram() {
        glDeleteProgram(m_id);
        spdlog::debug("Deleted shader prorgram (id: {})", m_id);
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
        GLuint loc = glGetUniformLocation(m_id, name.c_str());
        m_uniformCache[name] = loc;
        return loc;

    }

}
