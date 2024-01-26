#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : 
	m_position(position), 
	m_up(up), 
	m_front(glm::vec3(0.0f, 0.0f, -1.0f)),
	m_yaw(yaw), 
	m_pitch(pitch),
	m_speed(40.0f),
	m_sensitivity(25.0f),
	m_first_mouse(true)
{
	updateVectors();
}

Camera::~Camera()
{
}

void Camera::update(float delta_time)
{
	processKeyboard(delta_time);
	processMouse(delta_time);
}

const glm::vec3 &Camera::getPosition() const
{
	return m_position;
}

glm::mat4 Camera::getViewMatrix() const
{
	return glm::lookAt(m_position, m_position + m_front, m_up);
}

void Camera::updateVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	front.y = sin(glm::radians(m_pitch));
	front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_front = glm::normalize(front);
	m_right = glm::normalize(glm::cross(m_front, glm::vec3(0.0f, 1.0f, 0.0f)));
	m_up = glm::normalize(glm::cross(m_right, m_front));
}

void Camera::processKeyboard(float delta_time)
{
	float velocity = m_speed * delta_time;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		m_position += m_front * velocity;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		m_position -= m_front * velocity;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		m_position -= m_right * velocity;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		m_position += m_right * velocity;
}

void Camera::processMouse(float delta_time)
{
	float xpos = sf::Mouse::getPosition().x;
	float ypos = sf::Mouse::getPosition().y;

	if (m_first_mouse)
	{
		m_mouse_last_x = xpos;
		m_mouse_last_y = ypos;
		m_first_mouse = false;
	}

	float xoffset = xpos - m_mouse_last_x;
	float yoffset = m_mouse_last_y - ypos;

	m_mouse_last_x = xpos;
	m_mouse_last_y = ypos;
	
	m_yaw   += xoffset * delta_time * m_sensitivity;
	m_pitch += yoffset * delta_time * m_sensitivity;

	if (m_pitch > 90.0f)
		m_pitch = 90.0f;
	if (m_pitch < -90.0f)
		m_pitch = -90.0f;

	updateVectors();
}
