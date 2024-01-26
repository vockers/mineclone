#pragma once

#include <SFML/Graphics.hpp>

class Input
{
public:
	Input(sf::Window& window);
	~Input();

	void update();

	sf::Vector2i getMousePosition() const;
	void setMousePosition(int x, int y);

	void centerMousePosition();

	bool isCursorVisible() const;

private:
	sf::Window& m_window;

	bool m_keys_pressed[sf::Keyboard::KeyCount];
	bool m_keys_released[sf::Keyboard::KeyCount];
	bool m_keys_held[sf::Keyboard::KeyCount];

	bool m_mouse_buttons_pressed[sf::Mouse::ButtonCount];
	bool m_mouse_buttons_released[sf::Mouse::ButtonCount];
	bool m_mouse_buttons_held[sf::Mouse::ButtonCount];

	sf::Vector2i m_mouse_position;
	sf::Vector2i m_mouse_delta;

	bool m_cursor_visible;
};