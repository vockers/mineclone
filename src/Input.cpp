#include "Input.hpp"

#include <iostream>

namespace mc
{
	Input::Input(Window &window) : m_window(window),
								   m_cursor_visible(true)
	{
	}

	Input::~Input()
	{
	}

	void Input::update()
	{
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				m_window.close();
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
					m_window.close();
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					m_cursor_visible = !m_cursor_visible;
					SDL_ShowCursor(m_cursor_visible);
					SDL_SetRelativeMouseMode(m_cursor_visible ? SDL_FALSE : SDL_TRUE);
					centerMousePosition();
				}
				break;
			default:
				break;
			}
		}

		SDL_PumpEvents();
		m_keystate = SDL_GetKeyboardState(NULL);
	}

	glm::ivec2 Input::getMousePosition() const
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		return glm::ivec2(x, y);
	}

	bool Input::isKeyPressed(SDL_Scancode key) const
	{
		return m_keystate[key] == 1;
	}

	void Input::centerMousePosition()
	{
		SDL_WarpMouseInWindow(m_window.getWindow(), m_window.getSize().x / 2, m_window.getSize().y / 2);
	}
}