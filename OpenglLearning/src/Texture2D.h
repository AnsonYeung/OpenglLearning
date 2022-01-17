#pragma once
#include "base.h"
namespace opengllearning {
	class Texture2D {
	public:
		const GLuint id;
		Texture2D(GLenum texture, const char *filename);
		Texture2D(const Texture2D &) = delete;
		~Texture2D();
		operator bool();
	private:
		bool good = true;
		static GLuint makeTexture();
	};
}