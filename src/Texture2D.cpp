#include "Texture2D.h"
#include "stb_image.h"
#pragma warning(push)
#pragma warning(disable: 4005)
#include <spdlog/spdlog.h>
#pragma warning(pop)
namespace opengllearning {

	Texture2D::Texture2D(GLenum texture, const char *filename)
		: m_id(makeTexture()) {

		if (!m_id) {
			spdlog::critical("Cannot create new texture");
			glDeleteTextures(1, &m_id);
			m_id = 0;
			return;
		}

		stbi_set_flip_vertically_on_load(true);

		int width, height, nrChannels;
		unsigned char *textureData = stbi_load(filename, &width, &height, &nrChannels, 0);

		if (!textureData) {
			spdlog::critical("Failed to load texture \"{}\"", filename);
			glDeleteTextures(1, &m_id);
			m_id = 0;
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
		glBindTexture(GL_TEXTURE_2D, m_id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, sourceFileFormat, GL_UNSIGNED_BYTE, textureData);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(textureData);

		spdlog::debug("Created texture (id: {}) from file \"{}\"", m_id, filename);

	}

	Texture2D::~Texture2D() {
		if (m_id) {
			glDeleteTextures(1, &m_id);
			spdlog::debug("Deleted texture (id: {})", m_id);
		}
	}

	GLuint Texture2D::makeTexture() {
		GLuint texId;
		glGenTextures(1, &texId);
		return texId;
	}

	Texture2D::operator bool() {
		return m_id;
	}

} // opengllearning