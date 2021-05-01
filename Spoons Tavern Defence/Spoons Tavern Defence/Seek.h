#pragma once
#include "Transform.h"
#include "SteeringOutput.h"

class Seek
{
private:
	const spty::Transform &_character, &_target;

	float _maxAcceleration;

public:

	Seek();

	Seek(const spty::Transform& character, const spty::Transform& target, float maxAcceleration);

	SteeringOutput getSteering() const;
};