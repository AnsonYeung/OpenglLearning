#pragma once
#include "base.h"

namespace opengllearning {
    class Shader {
    public:
        const GLuint &id = m_id;
        Shader(const char *filename, GLenum type);
        Shader(const Shader &) = delete;
        ~Shader();
        operator bool();
    private:
        GLuint m_id;
    };
}
