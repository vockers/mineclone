#pragma once

#include <GL/glew.h>

class Shader
{
public:
	Shader();
	~Shader();

	void loadFromFile(const char* vertex_path, const char* fragment_path);
	void bind() const;

private:
	GLuint m_id;

	void build(const char* vertex_code, const char* fragment_code);
};