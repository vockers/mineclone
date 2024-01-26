#include "Game.hpp"

#include <SFML/OpenGL.hpp>

Game::Game() : 
	m_window(sf::VideoMode(800, 600), "Mineclone"),
	m_camera(glm::vec3(0.0f, 40.0f, 30.0f)),
	m_renderer(m_window, m_camera)
{
}

Game::~Game()
{
}

void Game::run()
{
	while (m_window.isOpen())
	{
		processEvents();
		update();
		m_renderer.render();
	}
}

void Game::processEvents()
{
	sf::Event event;

	while (m_window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_window.close();
			break;
		case sf::Event::Resized:
			m_renderer.setViewPort(event.size.width, event.size.height);
			break;
		default:
			break;
		}
	}
}

void Game::update()
{
	sf::Time delta_time = m_clock.restart();
	m_camera.update(delta_time.asSeconds());
}
