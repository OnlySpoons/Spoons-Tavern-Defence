#include "Camera.h"

namespace Spoonity {

	//Constructor
	Camera::Camera(glm::vec3 position, glm::vec3 front, float yaw, float pitch, float fov)
		: _position(position),
		_front(front),
		_yaw(yaw), _pitch(pitch)
	{
		updateCameraVectors();
	}

	//Returns the direction the player is looking to translate objects into view space
	glm::mat4 Camera::GetViewMatrix() const
	{
		return glm::lookAt(_position, _position + _front, _up);
	}

	//Reacalculates the cameras direction vectors
	void Camera::updateCameraVectors()
	{
		float pitch = glm::radians(_pitch);
		float yaw = glm::radians(_yaw);

		glm::vec3 front(0.0f);
		front.x = cos(yaw) * cos(pitch);
		front.y = sin(pitch);
		front.z = sin(yaw) * cos(pitch);
		_front = normalize(front);

		_right = glm::normalize(glm::cross(_front, WorldUp));
		_up = glm::normalize(glm::cross(_right, _front));
	}
}