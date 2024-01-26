#pragma once

#include <glm/glm.hpp>

#include "Input.hpp"

class Camera
{
public:
    Camera(
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
		float yaw = -90.0f, float pitch = 0.0f);
	~Camera();

	void update(float delta_time, Input& input);

	const glm::vec3& getPosition() const;
	glm::mat4 getViewMatrix() const;

private:
	glm::vec3 m_position;
	glm::vec3 m_direction;
	glm::vec3 m_up;
	glm::vec3 m_front;
	glm::vec3 m_right;

	float m_yaw;
	float m_pitch;

	float m_speed;
	float m_sensitivity;

	float m_mouse_last_x;
	float m_mouse_last_y;
	bool m_first_mouse;

	void updateVectors();
	void processKeyboard(float delta_time);
	void processMouse(float delta_time, Input& input);
};