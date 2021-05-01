#include "Align.h"

Align::Align(const spty::Transform& character, const spty::Transform& target,
	float angularAcceleration, float rotation,
	float targetRadius, float slowRadius
)	
	: _character(character), _target(target),
	_maxAngularAcceleration(angularAcceleration), _maxRotation(rotation),
	_targetRadius(targetRadius), _slowRadius(slowRadius)
{
}

SteeringOutput Align::getSteering() const
{
	SteeringOutput result{};

	float rotation = _target.getYaw() - _character.getYaw();

	rotation = std::abs(rotation) > spty::PI ? rotation - 2 * spty::PI : rotation;
	float rotationSize = std::abs(rotation);
	float targetRotation;

	if (rotationSize < _targetRadius)
		return result;

	if (rotationSize > _slowRadius)
		targetRotation = _maxRotation;
	else
		targetRotation = _maxRotation * rotationSize / _slowRadius;

	targetRotation *= rotation / rotationSize;

	//TODO: figure out how to add the commented section
	result._angular = targetRotation - _target.getAngularVelocity() / _timeToTarget;

	float angularAccel = std::abs(result._angular);
	if (angularAccel > _maxAngularAcceleration)
	{
		result._angular /= angularAccel;
		result._angular *= _maxAngularAcceleration;
	}

	result._linear = glm::vec3(0.0f);
	return result;
}