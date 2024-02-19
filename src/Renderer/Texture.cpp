#include "Texture.hpp"

#include <iostream>

#include "../Utils/stb_image.h"

Texture::~Texture()
{
	glDeleteTextures(1, &m_id);
}

void Texture::loadFromFile(const char *path)
{
	int width, height, channels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *img = stbi_load(path, &width, &height, &channels, 0);
	if (!img)
	{
		std::cerr << "Failed to load texture: " << path << std::endl;
		exit(1);
	}
	GLenum format = channels == 3 ? GL_RGB : GL_RGBA;

	glGenTextures(1, &m_id);
	glBindTexture(GL_TEXTURE_2D, m_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, img);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(img);
}

void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, m_id);
}
