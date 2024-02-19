#include "Renderer.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/Image.hpp>
#include <GL/glew.h>

Renderer::Renderer(sf::Window &window, Camera &camera) : 
	m_window(window),
	m_camera(camera),
	m_projection_settings({ 45.0f, (float)window.getSize().x / (float)window.getSize().y, 0.1f, 1000.0f })
{
	GLenum glew_status = glewInit();
	if (glew_status != GLEW_OK)
	{
		std::cerr << "Error: glewInit failed: " << glewGetErrorString(glew_status) << std::endl;
		exit(1);
	}

	setViewPort(window.getSize().x, window.getSize().y);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);

	m_shaders[SHADER_CHUNK].loadFromFile("res/shaders/chunk_vertex.glsl", "res/shaders/chunk_fragment.glsl");
	m_shaders[SHADER_CHUNK].bind();
    m_shaders[SHADER_CHUNK].setUniform("tex", 0);

	m_shaders[SHADER_CUBEMAP].loadFromFile("res/shaders/cubemap_vertex.glsl", "res/shaders/cubemap_fragment.glsl");
	m_shaders[SHADER_CUBEMAP].bind();
    m_shaders[SHADER_CUBEMAP].setUniform("tex", 0);

	m_textures[TEXTURE_BLOCKS].loadFromFile("res/textures/blocks.png");

	m_skybox.generate("res/textures/sky/top.png", "res/textures/sky/bottom.png", "res/textures/sky/left.png", "res/textures/sky/right.png", "res/textures/sky/front.png", "res/textures/sky/back.png");
}

Renderer::~Renderer()
{
}

void Renderer::renderPrepare()
{
	setViewPort(m_window.getSize().x, m_window.getSize().y);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glClearColor(0.3f, 0.3f, 0.8f, 1.0f);

	glActiveTexture(GL_TEXTURE0);
	m_textures[TEXTURE_BLOCKS].bind();
	m_shaders[SHADER_CHUNK].bind();
	m_shaders[SHADER_CHUNK].setUniform("projection", getProjectionMatrix());
	m_shaders[SHADER_CHUNK].setUniform("view", m_camera.getViewMatrix());
}

void Renderer::renderSkybox()
{
	glDepthFunc(GL_LEQUAL);
	m_shaders[SHADER_CUBEMAP].bind();
	m_shaders[SHADER_CUBEMAP].setUniform("projection", getProjectionMatrix());
	glm::mat4 view = glm::mat4(glm::mat3(m_camera.getViewMatrix())); // remove translation from the view matrix
	m_shaders[SHADER_CUBEMAP].setUniform("view", view);
	m_skybox.draw();
	glDepthFunc(GL_LESS);
}

void Renderer::setViewPort(int width, int height)
{
	glViewport(0, 0, width, height);
	m_projection_settings.aspect = (float)width / (float)height;
}

glm::mat4 Renderer::getProjectionMatrix() const
{
	return glm::perspective(
		glm::radians(m_projection_settings.fov),
		m_projection_settings.aspect,
		m_projection_settings.near,
		m_projection_settings.far
	);
}
