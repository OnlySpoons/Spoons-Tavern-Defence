#pragma once
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
		SteeringBehaviour _behaviour;
		float _weight;
	};

	using BehaviourList = std::vector<BehaviourAndWeight>;

private:
	BehaviourList _behaviours;

	float _maxAcceleration;
	float _maxAngularAcceleration;

public:

	BlendedSteering(std::vector<BehaviourAndWeight> behvaiours, float acceleration, float angularAcceleration);

	SteeringOutput getSteering() const;

	glm::vec3 getTargetPosition() const;
};