#pragma once

#include <glm/glm.hpp>

#include "Window.hpp"

namespace mc
{
	class Input
	{
	public:
		Input(Window &window);
		~Input();

		void update();

		glm::ivec2 getMousePosition() const;
		bool isKeyPressed(SDL_Scancode key) const;

		void centerMousePosition();

		bool isCursorVisible() const { return m_cursor_visible; }

	private:
		Window &m_window;

		bool m_cursor_visible;
		const Uint8 *m_keystate;
	};
}