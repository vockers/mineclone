#pragma once

#include <SDL2/SDL.h>

#include "Renderer/Renderer.hpp"
#include "World/World.hpp"
#include "Window.hpp"
#include "Input.hpp"
#include "GUI/GUI.hpp"
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
	void update();
	void render();

	Window m_window;
	Input m_input;
	Camera m_camera;
	Renderer m_renderer;
	World m_world;
	GUI m_gui;
	HUD m_hud;

	int m_current_time;
};
