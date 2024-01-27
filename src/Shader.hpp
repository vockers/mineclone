#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>

enum ShaderType
{
	SHADER_CHUNK,
};

constexpr int SHADER_COUNT = SHADER_CHUNK + 1;

class Shader
{
public:
	Shader() = default;
	~Shader();

	void loadFromFile(const char* vertex_path, const char* fragment_path);
	void bind();

	void setUniform(const char* name, const glm::mat4 value);
	void setUniform(const char* name, const int value);

private:
	GLuint m_id;

	void build(const char* vertex_code, const char* fragment_code);
};