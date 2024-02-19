#include "Game.hpp"

#include <SFML/OpenGL.hpp>

Game::Game() : 
	m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mineclone", sf::Style::Default, sf::ContextSettings(24, 8, 0, 3, 3)),
	m_input(m_window),
	m_camera(glm::vec3(0.0f, 40.0f, 30.0f)),
	m_renderer(m_window, m_camera),
	m_world(m_camera, m_renderer)
{
}

Game::~Game()
{
}

void Game::run()
{
	while (m_window.isOpen())
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
	sf::Time delta_time = m_clock.restart();
	m_camera.update(delta_time.asSeconds(), m_input);
}
