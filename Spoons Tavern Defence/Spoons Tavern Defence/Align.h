#pragma once
/*
Group Name: OnlySpoons

Members: Martin Harvey(B00329330), Thomas Cole(B00269678) & Harry Durham(B00347454)

We declare that the following code was produced by OnlySpoons as a group assignment for the CGT Group Project module and that it is our own work.

We are aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.
*/
#include "Transform.h"
#include "SteeringOutput.h"
#include "MathConstants.h"

class Align
{
//Variables
private:
	const spty::Transform &character_, &target_;
	float maxAngularAcceleration_, maxRotation_;
	float targetRadius_, slowRadius_;
	float timeToTarget_ = 0.1f;

//Functions
public:
	//Constructor
	Align(const spty::Transform& character, const spty::Transform& target,
		float angularAcceleration, float rotation,
		float targetRadius, float slowRadius);

	SteeringOutput getSteering() const;

	glm::vec3 getTargetPosition() const { return target_.getPosition(); }
};