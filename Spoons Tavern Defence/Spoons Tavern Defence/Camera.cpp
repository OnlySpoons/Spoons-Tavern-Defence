#include "Camera.h"

namespace spty {
	
	Camera::Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up, float fov)
		: position_(position),
		front_(front),
		up_(up),
		fov_(fov)
	{
	}

	void Camera::update(const Transform& transform, const glm::vec3& cameraOffset)
	{
		setPosition(transform.getPosition() + cameraOffset);
		setFront(transform.getFront());
		setUp(transform.getUp());
	}
}