#include "Game.hpp"

#include <SFML/OpenGL.hpp>

Game::Game() : 
	m_window(WINDOW_WIDTH, WINDOW_HEIGHT, "Mineclone"),
	m_input(m_window),
	m_camera(glm::vec3(0.0f, 40.0f, 30.0f)),
	m_renderer(m_window, m_camera),
	m_world(m_camera, m_renderer)
{
	m_current_time = SDL_GetTicks();
}

Game::~Game()
{
}

void Game::run()
{
	while (!m_window.isClosed())
	{
		m_input.update();
		update();
		m_renderer.renderPrepare();
		m_world.render();
		m_renderer.renderSkybox();
		m_window.display();
	}
	m_world.getUpdateThread().join();
}

void Game::update()
{
	int last_time = m_current_time;
	m_current_time = SDL_GetTicks();
	float delta_time = (m_current_time - last_time) / 1000.0f;
	m_camera.update(delta_time, m_input);
}
