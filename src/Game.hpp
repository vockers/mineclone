#pragma once

#include <SDL2/SDL.h>

#include "Renderer/Renderer.hpp"
#include "World/World.hpp"
#include "Window.hpp"
#include "Input.hpp"
#include "GUI/HUD.hpp"

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

	Window m_window;
	int m_current_time;
	Input m_input;
	Camera m_camera;
	Renderer m_renderer;
	World m_world;
	HUD m_hud;
};