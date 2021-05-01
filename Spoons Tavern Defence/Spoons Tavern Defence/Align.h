#pragma once
#include "Transform.h"
#include "SteeringOutput.h"
#include "MathConstants.h"

class Align
{
private:
	const spty::Transform& _character, & _target;
	float _maxAngularAcceleration, _maxRotation;
	float _targetRadius, _slowRadius;
	float _timeToTarget = 0.1f;

public:

	Align(const spty::Transform& character,	const spty::Transform& target,
		  float angularAcceleration,	float rotation,
		  float targetRadius,			float slowRadius
	);

	SteeringOutput getSteering() const;
};