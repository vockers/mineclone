#include "Input.hpp"

#include <iostream>

Input::Input(sf::Window &window) :
	m_window(window),
	m_cursor_visible(true)
{
}

Input::~Input()
{
}

void Input::update()
{
	sf::Event event;

	while (m_window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_window.close();
			break;
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
				m_window.close();
			break;
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				m_cursor_visible = !m_cursor_visible;
				m_window.setMouseCursorVisible(m_cursor_visible);
				m_window.setMouseCursorGrabbed(!m_cursor_visible);
			}
			break;
		default:
			break;
		}
	}
}

sf::Vector2i Input::getMousePosition() const
{
	return sf::Mouse::getPosition(m_window);
}

void Input::setMousePosition(int x, int y)
{
	sf::Mouse::setPosition(sf::Vector2i(x, y), m_window);
}

void Input::centerMousePosition()
{
	setMousePosition(m_window.getSize().x / 2, m_window.getSize().y / 2);
}

bool Input::isCursorVisible() const
{
	return m_cursor_visible;
}
