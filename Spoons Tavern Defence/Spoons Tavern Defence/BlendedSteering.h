#pragma once
/*
Group Name: OnlySpoons

Members: Martin Harvey(B00329330), Thomas Cole(B00269678) & Harry Durham(B00347454)

We declare that the following code was produced by OnlySpoons as a group assignment for the CGT Group Project module and that it is our own work.

We are aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.
*/
#include <vector>
#include <variant>

#include "Seek.h"
#include "Align.h"

class BlendedSteering
{
public:
	struct BehaviourAndWeight
	{
		using SteeringBehaviour = std::variant<Seek, Align>;
		SteeringBehaviour Behaviour;
		float Weight;
	};

	using BehaviourList = std::vector<BehaviourAndWeight>;

//Variables
private:
	BehaviourList behaviours_;

	float maxAcceleration_;
	float maxAngularAcceleration_;

//Functions
public:
	BlendedSteering(std::vector<BehaviourAndWeight> behvaiours, float acceleration, float angularAcceleration);

	SteeringOutput getSteering() const;

	glm::vec3 getTargetPosition() const;
};