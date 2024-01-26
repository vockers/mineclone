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
	sf::Clock m_clock;
	Camera m_camera;
	Renderer m_renderer;
};