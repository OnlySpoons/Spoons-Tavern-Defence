#include "Camera.h"

namespace GameEngine {

	//Constructor
	Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
		: _Front(glm::vec3(0.0f, 0.0f, -1.0f)), _MovementSpeed(SPEED), _MouseSensitivity(SENSITIVITY), _Zoom(ZOOM)
	{
		_Position = position;
		_WorldUp = up;
		_Yaw = yaw;
		_Pitch = pitch;

		updateCameraVectors();
	}

	//Returns the direction the player is looking to translate objects into view space
	glm::mat4 Camera::GetViewMatrix() const
	{
		return glm::lookAt(_Position, _Position + _Front, _Up);
	}

	//Processes the keyboard input to control camera movement
	void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime, bool isSprinting)
	{
		float velocity = _MovementSpeed * deltaTime;
		if (isSprinting)
			velocity *= 2;
		if (direction == Camera_Movement::FORWARD)
			_Position += _Front * velocity;
		if (direction == Camera_Movement::BACKWARD)
			_Position -= _Front * velocity;
		if (direction == Camera_Movement::LEFT)
			_Position -= _Right * velocity;
		if (direction == Camera_Movement::RIGHT)
			_Position += _Right * velocity;

		//keep player on ground level
		//_Position.y = 0.0f;
	}

	//Processes the mouse movement to control where the camera is facing
	void Camera::ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch)
	{
		xOffset *= _MouseSensitivity;
		yOffset *= _MouseSensitivity;

		_Yaw += xOffset;
		_Pitch += yOffset;

		if (constrainPitch)
		{
			if (_Pitch > 89.0f)
				_Pitch = 89.0f;
			if (_Pitch < -89.0f)
				_Pitch = -89.0f;
		}

		updateCameraVectors();
	}

	//Processes the scroll wheel to control the zoom]
	void Camera::ProcessMouseScroll(float yOffset)
	{
		if (_Zoom >= 1.0f && _Zoom <= ZOOM)
			_Zoom -= yOffset;
		if (_Zoom < 1.0f)
			_Zoom = 1.0f;
		if (_Zoom > 45.0f)
			_Zoom = 45.0f;
	}

	//Reacalculates the cameras direction vectors
	void Camera::updateCameraVectors()
	{
		glm::vec3 front(0.0f);
		front.x = cos(glm::radians(_Yaw)) * cos(glm::radians(_Pitch));
		front.y = sin(glm::radians(_Pitch));
		front.z = sin(glm::radians(_Yaw)) * cos(glm::radians(_Pitch));
		_Front = normalize(front);

		_Right = glm::normalize(glm::cross(_Front, _WorldUp));
		_Up = glm::normalize(glm::cross(_Right, _Front));
	}
}