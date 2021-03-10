#include "Camera.h"

namespace Spoonity {

	//Constructor
	Camera::Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up, float fov)
		: _position(position),
		_front(front),
		_up(up),
		_fov(fov)
	{
	}

	//Update all variables
	void Camera::update(const Transform& transform, const glm::vec3& cameraOffset)
	{
		setPosition(transform.getPosition() + cameraOffset);
		setFront(transform.getFront());
		setUp(transform.getUp());
	}

	//Setters
	void Camera::setPosition(const glm::vec3& position) { _position = position; }

	void Camera::setFront(const glm::vec3& front) { _front = front; }

	void Camera::setUp(const glm::vec3& up) { _up = up; }

	void Camera::setFOV(const float& fov) { _fov = fov; }

	//Getters
	glm::vec3 Camera::getPosition() const { return _position; }

	glm::vec3 Camera::getFront() const { return _front; }

	glm::vec3 Camera::getUp() const { return _up; }

	float Camera::getFOV() const { return _fov; }


	//Returns the direction the player is looking to translate objects into view space
	glm::mat4 Camera::GetViewMatrix() const
	{
		return glm::lookAt(_position, _position + _front, _up);
	}
}