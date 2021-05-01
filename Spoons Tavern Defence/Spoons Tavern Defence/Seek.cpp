#include "Seek.h"

Seek::Seek(const spty::Transform& character, const spty::Transform& target, float maxAcceleration)
	: _character(character), _target(target), _maxAcceleration(maxAcceleration)
{
}

SteeringOutput Seek::getSteering() const
{
	SteeringOutput result;
	result._linear = glm::normalize( _target.getPosition() - _character.getPosition() ) * _maxAcceleration;
	result._angular = 0;
	return result;
}