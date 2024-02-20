#include "Game.hpp"

Game::Game() : 
	m_window(WINDOW_WIDTH, WINDOW_HEIGHT, "Mineclone"),
	m_input(m_window),
	m_camera(glm::vec3(0.0f, 40.0f, 30.0f)),
	m_renderer(m_window, m_camera),
	m_world(m_camera, m_renderer),
	m_gui(m_renderer),
	m_hud(m_gui)
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
		update();
		render();
	}
	m_world.getUpdateThread().join();
}

void Game::update()
{
	int last_time = m_current_time;
	m_current_time = SDL_GetTicks();
	float delta_time = (m_current_time - last_time) / 1000.0f;

	m_input.update();
	m_camera.update(delta_time, m_input);
	m_hud.update(delta_time);
}

void Game::render()
{
	m_renderer.renderPrepare();
	m_world.render();
	m_renderer.renderSkybox();
	m_gui.render();
	m_hud.render();
	m_window.display();
}
