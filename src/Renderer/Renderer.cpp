#include "Renderer/Renderer.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <GL/glew.h>

namespace mc
{
	Renderer::Renderer(Window &window, Camera &camera) : m_window(window),
														 m_camera(camera),
														 m_projection_settings({45.0f, (float)window.getSize().x / (float)window.getSize().y, 0.1f, 1000.0f})
	{
		GLenum glew_status = glewInit();
		if (glew_status != GLEW_OK)
			throw std::runtime_error("Error: " + std::string((const char *)glewGetErrorString(glew_status)));

		setViewPort(window.getSize().x, window.getSize().y);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_CULL_FACE);

		m_cubemap_shader.loadFromFile("assets/shaders/cubemap_vertex.glsl", "assets/shaders/cubemap_fragment.glsl");

		m_skybox.generate(
			"assets/textures/sky/top.png",
			"assets/textures/sky/bottom.png",
			"assets/textures/sky/left.png",
			"assets/textures/sky/right.png",
			"assets/textures/sky/front.png",
			"assets/textures/sky/back.png");
	}

	Renderer::~Renderer()
	{
	}

	void Renderer::renderPrepare()
	{
		setViewPort(m_window.getSize().x, m_window.getSize().y);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.3f, 0.3f, 0.8f, 1.0f);
	}

	void Renderer::renderSkybox()
	{
		glDepthFunc(GL_LEQUAL);
		m_cubemap_shader.bind();
		m_cubemap_shader.setUniform("projection", getProjectionMatrix());
		glm::mat4 view = glm::mat4(glm::mat3(m_camera.getViewMatrix())); // remove translation from the view matrix
		m_cubemap_shader.setUniform("view", view);
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
			m_projection_settings.far);
	}

	glm::mat4 Renderer::getOrthoMatrix() const
	{
		return glm::ortho(0.0f, (float)m_window.getSize().x, 0.0f, (float)m_window.getSize().y);
	}
}