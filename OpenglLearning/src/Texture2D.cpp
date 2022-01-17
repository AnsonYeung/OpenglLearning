#include "Texture2D.h"
#include "stb_image.h"
#pragma warning(push)
#pragma warning(disable: 4005)
#include <spdlog/spdlog.h>
#pragma warning(pop)
namespace opengllearning {

	Texture2D::Texture2D(GLenum texture, const char *filename)
		: id(makeTexture()) {

		if (!id) {
			spdlog::critical("Cannot create new texture");
			good = false;
			return;
		}

		stbi_set_flip_vertically_on_load(true);

		int width, height, nrChannels;
		unsigned char *textureData = stbi_load(filename, &width, &height, &nrChannels, 0);

		if (!textureData) {
			spdlog::critical("Failed to load texture \"{}\"", filename);
			good = false;
			return;
		}

		spdlog::info("texture \"{}\" has {} channels", filename, nrChannels);

		GLenum sourceFileFormat;

		switch (nrChannels) {
		case 3:
			sourceFileFormat = GL_RGB;
			break;
		case 4:
			sourceFileFormat = GL_RGBA;
			break;
		default:
			spdlog::error("texture \"{}\" has {} channels, assuming GL_RGB", filename, nrChannels);
			sourceFileFormat = GL_RGB;
			break;
		}

		glActiveTexture(texture);
		glBindTexture(GL_TEXTURE_2D, id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, sourceFileFormat, GL_UNSIGNED_BYTE, textureData);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(textureData);

	}

	Texture2D::~Texture2D() {
		if (id) {
			glDeleteTextures(1, &id);
		}
	}

	GLuint Texture2D::makeTexture() {
		GLuint texId;
		glGenTextures(1, &texId);
		return texId;
	}

	Texture2D::operator bool() {
		return good;
	}

} // opengllearning