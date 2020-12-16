#include "Camera.h"

namespace Spoonity {

	//Constructor
	Camera::Camera(glm::vec3 position, glm::vec3 front, float yaw, float pitch)
		: _Position(position),
		  _Front(front),
		  _Yaw(yaw), _Pitch(pitch)
	{
		updateCameraVectors();
	}

	//Returns the direction the player is looking to translate objects into view space
	glm::mat4 Camera::GetViewMatrix() const
	{
		return glm::lookAt(_Position, _Position + _Front, _Up);
	}

	//Reacalculates the cameras direction vectors
	void Camera::updateCameraVectors()
	{
		glm::vec3 front(0.0f);
		front.x = cos(_Yaw) * cos(_Pitch);
		front.y = sin(_Pitch);
		front.z = sin(_Yaw) * cos(_Pitch);
		_Front = normalize(front);

		_Right = glm::normalize(glm::cross(_Front, _WorldUp));
		_Up = glm::normalize(glm::cross(_Right, _Front));
	}
}