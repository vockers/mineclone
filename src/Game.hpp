#pragma once

#include <SFML/Graphics.hpp>

#include "Renderer.hpp"

class Game
{
public:
	Game();
	~Game();

	void run();

private:
	void processEvents();
	void update();

	sf::Window m_window;
	Renderer m_renderer;
};