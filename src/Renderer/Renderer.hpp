#pragma once

#include <memory>
#include <vector>
#include <GL/glew.h>
#include <SFML/Graphics.hpp>

#include "../Camera.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Cubemap.hpp"

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

	void renderPrepare();
	void renderSkybox();
	void setViewPort(int width, int height);

	const Shader& getShader(ShaderType type) const { return m_shaders[type]; }

private:
	sf::Window&	m_window;
	Camera& m_camera;

	ProjectionSettings m_projection_settings;
	Shader m_shaders[SHADER_COUNT];
	Texture m_textures[TEXTURE_COUNT];
	Cubemap m_skybox;

	glm::mat4 getProjectionMatrix() const;
};