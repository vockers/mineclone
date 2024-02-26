#include "Texture.hpp"

#include <iostream>

#include "../Utils/stb_image.h"

namespace mc
{
	Texture::Texture() : m_id(0), m_format(GL_RGB), m_width(0), m_height(0)
	{
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_id);
	}

	void Texture::loadFromFile(const std::string& path)
	{
		int channels;
		stbi_set_flip_vertically_on_load(true);
		unsigned char *img = stbi_load(path.c_str(), &m_width, &m_height, &channels, 0);
		if (!img)
		{
			std::cerr << "Failed to load texture: " << path << std::endl;
			exit(1);
		}
		m_format = channels == 3 ? GL_RGB : GL_RGBA;
		m_data = std::vector<unsigned char>(img, img + m_width * m_height * channels);
		generate();
		stbi_image_free(img);
	}

	void Texture::bind()
	{
		glBindTexture(GL_TEXTURE_2D, m_id);
	}

	void Texture::generate()
	{
		glGenTextures(1, &m_id);
		glBindTexture(GL_TEXTURE_2D, m_id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, m_format, m_width, m_height, 0, m_format, GL_UNSIGNED_BYTE, m_data.data());
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);

		m_data.resize(0);
	}
}