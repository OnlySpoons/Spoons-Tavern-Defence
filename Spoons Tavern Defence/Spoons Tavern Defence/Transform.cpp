#include "Transform.h"

namespace Spoonity {

	//Constructor
	Transform::Transform(const glm::vec3& pos,
		const glm::vec3& rot,
		const glm::vec3& scale)
		: _pos(pos), _rot(rot), _scale(scale)
	{
		constrainPitch();
	}

	//Destructor
	Transform::~Transform() {}

	//Setters for transform data
	void Transform::setPosition(const glm::vec3& translation) { _pos = translation; }

	void Transform::setScale(const glm::vec3& scaling) { _scale = scaling; }

	void Transform::setRotation(const glm::vec3& rotation) { _rot = rotation; constrainPitch(); }

	//Getters for transform data
	glm::vec3 Transform::getPosition() const { return _pos; }

	glm::vec3 Transform::getScale() const { return _scale; }

	glm::vec3 Transform::getRotation() const { return _rot; }

	//Getters for direction vectors
	glm::vec3 Transform::getRight() const
	{
		glm::vec3 right;
		right.x = sin(glm::radians(_rot.x + 90.0f)) * cos(glm::radians(_rot.y));
		right.y = sin(glm::radians(_rot.y));
		right.z = -cos(glm::radians(_rot.x + 90.0f)) * cos(glm::radians(_rot.y));

		return glm::normalize(right);
	}

	glm::vec3 Transform::getUp() const
	{
		glm::vec3 up;
		up.x = sin(glm::radians(_rot.x)) * cos(glm::radians(_rot.y +90.0f));
		up.y = sin(glm::radians(_rot.y + 90.0f));
		up.z = -cos(glm::radians(_rot.x)) * cos(glm::radians(_rot.y + 90.0f));
		return glm::normalize(up);
	}

	glm::vec3 Transform::getFront() const 
	{ 
		glm::vec3 front;
		front.x = sin(glm::radians(_rot.x)) * cos(glm::radians(_rot.y));
		front.y = sin(glm::radians(_rot.y));
		front.z = -cos(glm::radians(_rot.x)) * cos(glm::radians(_rot.y));

		return glm::normalize(front);
	}

	//Getter for the transform matrix
	glm::mat4 Transform::getMatrix() const
	{
		glm::mat4 posMatrix = glm::translate(_pos);

		glm::mat4 rotXMatrix = glm::rotate(glm::radians(_rot.x), WorldDir::DOWN);
		glm::mat4 rotYMatrix = glm::rotate(glm::radians(_rot.y), WorldDir::LEFT);
		glm::mat4 rotZMatrix = glm::rotate(glm::radians(_rot.z), WorldDir::BACK);
		glm::mat4 rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;

		glm::mat4 scaleMatrix = glm::scale(_scale);

		return posMatrix * rotMatrix * scaleMatrix;
	}

	//Utility functions
	void Transform::move(const glm::vec3& dir) { _pos += dir; }

	//Rotation functions
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

	void Transform::pitch(const float& angle) { _rot.y += angle; constrainPitch(); }

	void Transform::yaw(const float& angle) { _rot.x += angle; }

	void Transform::roll(const float& angle) { _rot.z += angle; }

	//Getters for specific rotations
	float Transform::getPitch() const { return _rot.y; }

	float Transform::getYaw() const { return _rot.x; }

	float Transform::getRoll() const { return _rot.z; }

/*--------------- 
Private Functions
---------------*/

	//Keep pitch from inverting
	void Transform::constrainPitch()
	{
		if (_rot.y > 89.0f)
			_rot.y = 89.0f;
		if (_rot.y < -89.0f)
			_rot.y = -89.0f;
	}
}