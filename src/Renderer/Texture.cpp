#include "Texture.hpp"

#include <SFML/Graphics/Image.hpp>

Texture::~Texture()
{
	glDeleteTextures(1, &m_id);
}

void Texture::loadFromFile(const char *path)
{
	sf::Image img;
	img.loadFromFile(path);
	img.flipVertically();

	glGenTextures(1, &m_id);
	glBindTexture(GL_TEXTURE_2D, m_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.getSize().x, img.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.getPixelsPtr());
	glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, m_id);
}
