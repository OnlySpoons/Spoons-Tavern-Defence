#include "Seek.h"

Seek::Seek(const spty::Transform& character, const spty::Transform& target, float maxAcceleration)
	: character_(character), target_(target), maxAcceleration_(maxAcceleration)
{
}

SteeringOutput Seek::getSteering() const
{
	SteeringOutput result;
	result.Linear = glm::normalize( target_.getPosition() - character_.getPosition() ) * maxAcceleration_;
	result.Angular = 0;
	return result;
}