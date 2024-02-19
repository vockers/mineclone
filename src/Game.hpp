#pragma once

#include <SFML/Graphics.hpp>

#include "Renderer/Renderer.hpp"
#include "World/World.hpp"
#include "Input.hpp"

constexpr int WINDOW_WIDTH = 1280;
constexpr int WINDOW_HEIGHT = 720;

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