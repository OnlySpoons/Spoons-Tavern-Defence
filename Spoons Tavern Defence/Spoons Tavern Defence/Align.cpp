#include "Align.h"

Align::Align(const spty::Transform& character, const spty::Transform& target,
	float angularAcceleration, float rotation, float targetRadius, float slowRadius)
	: character_(character), target_(target),
	maxAngularAcceleration_(angularAcceleration), maxRotation_(rotation),
	targetRadius_(targetRadius), slowRadius_(slowRadius)
{
}

SteeringOutput Align::getSteering() const
{
	SteeringOutput result{};

	float rotation = target_.getYaw() - character_.getYaw();

	rotation = std::abs(rotation) > spty::PI ? rotation - 2 * spty::PI : rotation;
	float rotationSize = std::abs(rotation);

	float targetRotation =
		rotationSize <= slowRadius_ ?
		maxRotation_ * rotationSize / slowRadius_
		: maxRotation_;

	targetRotation *= rotation / rotationSize;

	//TODO: figure out how to add the commented section
	float temp = targetRotation - target_.getAngularVelocity() / timeToTarget_;

	result.Angular = 
		abs(temp) > maxAngularAcceleration_ ?
		temp / abs(temp) * maxAngularAcceleration_
		: temp;

	result.Linear = glm::vec3(0.0f);
	return result;
}