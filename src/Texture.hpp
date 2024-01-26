#pragma once

#include <GL/glew.h>

enum TextureType
{
	TEXTURE_BLOCKS,
};

#define TEXTURE_COUNT TEXTURE_BLOCKS + 1

class Texture
{
public:
	Texture();
	~Texture();

	void loadFromFile(const char* path);
	void bind();

private:
	GLuint m_id;
};