#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
    Camera(
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), 
		float yaw = -90.0f, float pitch = 0.0f);
	~Camera();

	void update(float dt);

	glm::mat4 getViewMatrix() const;
	glm::mat4 getProjectionMatrix() const;

	glm::vec3 getPosition() const;
	glm::vec3 getDirection() const;

	void setPosition(const glm::vec3& position);
	void setDirection(const glm::vec3& direction);

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
	float m_fov;
	float m_aspectRatio;
	float m_nearPlane;
	float m_farPlane;

	void updateVectors();
};