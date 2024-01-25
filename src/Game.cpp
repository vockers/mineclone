#include "Game.hpp"

#include <SFML/OpenGL.hpp>

Game::Game() : m_window(sf::VideoMode(800, 600), "Mineclone"), m_renderer(m_window)
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
		default:
			break;
		}
	}
}

void Game::update()
{
}
