#pragma once

#include <memory>
#include <vector>
#include <GL/glew.h>
#include <SFML/Graphics.hpp>

#include "Camera.hpp"
#include "Shader.hpp"

enum TextureType
{
	TEXTURE_BLOCKS,
};

#define TEXTURE_COUNT TEXTURE_BLOCKS + 1

struct ProjectionSettings
{
	float fov;
	float aspect;
	float near;
	float far;
};

class Renderer
{
public:
	Renderer(sf::Window& window, Camera& camera);
	~Renderer();

	void render();
	void setViewPort(int width, int height);

private:
	sf::Window&	m_window;
	Camera& m_camera;

	ProjectionSettings m_projection_settings;
	Shader m_shaders[SHADER_COUNT];
	sf::Texture m_textures[TEXTURE_COUNT];

	glm::mat4 getProjectionMatrix() const;
};