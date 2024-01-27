#pragma once

#include <SFML/Graphics.hpp>

#include "Renderer.hpp"
#include "World/World.hpp"
#include "Input.hpp"

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
	Input m_input;
	Camera m_camera;
	World m_world;
	Renderer m_renderer;
};