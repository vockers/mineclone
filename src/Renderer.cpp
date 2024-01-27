#include "Renderer.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/Image.hpp>
#include <GL/glew.h>

#include "World/Chunk.hpp"
#include "World/ChunkMesh.hpp"

Renderer::Renderer(sf::Window &window, Camera &camera, World &world) : 
	m_window(window),
	m_camera(camera),
	m_world(world),
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

	m_shaders[SHADER_CHUNK].loadFromFile("res/shaders/chunk_vertex.glsl", "res/shaders/chunk_fragment.glsl");

	m_textures[TEXTURE_BLOCKS].loadFromFile("res/textures/blocks.png");

	m_shaders[SHADER_CHUNK].bind();
    m_shaders[SHADER_CHUNK].setUniform("tex", 0);

	m_world.updateChunks();
}

Renderer::~Renderer()
{
}

void Renderer::render()
{
	setViewPort(m_window.getSize().x, m_window.getSize().y);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glClearColor(0.3f, 0.3f, 0.8f, 1.0f);

	glActiveTexture(GL_TEXTURE0);
	m_textures[TEXTURE_BLOCKS].bind();
	m_shaders[SHADER_CHUNK].bind();

    glm::mat4 projection = getProjectionMatrix();
	m_shaders[SHADER_CHUNK].setUniform("projection", projection);
    glm::mat4 view = m_camera.getViewMatrix();
	m_shaders[SHADER_CHUNK].setUniform("view", view);

	for (auto it = m_world.getChunks().begin(); it != m_world.getChunks().end(); it++)
	{
		Chunk *chunk = it->second.get();
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(chunk->getPosition().x * CHUNK_SIZE, 0.0f, chunk->getPosition().y * CHUNK_SIZE));
		m_shaders[SHADER_CHUNK].setUniform("model", model);
		chunk->getMesh()->draw();
	}

	m_window.display();
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
