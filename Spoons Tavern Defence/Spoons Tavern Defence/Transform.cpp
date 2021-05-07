#include "Transform.h"

namespace spty {

	//Constructor
	Transform::Transform(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale)
		: pos_(pos), rot_(rot), scale_(scale)
	{
		constrainPitch();
	}

	//Destructor
	Transform::~Transform() {}

	glm::vec3 Transform::getFront() const 
	{ 
		glm::vec3 front;
		front.x = sin(glm::radians(rot_.x)) * cos(glm::radians(rot_.y));
		front.y = sin(glm::radians(rot_.y));
		front.z = -cos(glm::radians(rot_.x)) * cos(glm::radians(rot_.y));
		return glm::normalize(front);
	}

	glm::vec3 Transform::getRight() const
	{
		glm::vec3 right;
		right.x = sin(glm::radians(rot_.x + 90.0f)) * cos(glm::radians(rot_.y));
		right.y = sin(glm::radians(rot_.y));
		right.z = -cos(glm::radians(rot_.x + 90.0f)) * cos(glm::radians(rot_.y));
		return glm::normalize(right);
	}

	glm::vec3 Transform::getUp() const
	{
		glm::vec3 up;
		up.x = sin(glm::radians(rot_.x)) * cos(glm::radians(rot_.y + 90.0f));
		up.y = sin(glm::radians(rot_.y + 90.0f));
		up.z = -cos(glm::radians(rot_.x)) * cos(glm::radians(rot_.y + 90.0f));
		return glm::normalize(up);
	}


	glm::mat4 Transform::getMatrix() const
	{
		glm::mat4 matrix = glm::mat4(1.0f);
		
		matrix = glm::translate(matrix, pos_);
		matrix = glm::scale(matrix, scale_);

		matrix = glm::rotate(matrix, glm::radians(rot_.x), WorldDir::DOWN);
		matrix = glm::rotate(matrix, glm::radians(rot_.y), WorldDir::LEFT);
		matrix = glm::rotate(matrix, glm::radians(rot_.z), WorldDir::BACK);

		return matrix;
	}

	void Transform::rotate(const float& angle, Axis axis)
	{
		switch (axis)
		{
		case Axis::X:
			pitch(angle);
			break;
		case Axis::Y:
			yaw(angle);
			break;
		case Axis::Z:
			roll(angle);
			break;
		}
	}

	void Transform::constrainPitch()
	{
		if (rot_.y > 89.0f)
			rot_.y = 89.0f;
		if (rot_.y < -89.0f)
			rot_.y = -89.0f;
	}
}