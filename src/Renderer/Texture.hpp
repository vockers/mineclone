#pragma once

#include <GL/glew.h>

class Texture
{
public:
	Texture() = default;
	~Texture();

	void loadFromFile(const char* path);
	void bind();

private:
	GLuint m_id;
};
