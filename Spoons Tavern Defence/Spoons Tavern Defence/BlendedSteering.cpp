#include "BlendedSteering.h"

BlendedSteering::BlendedSteering(std::vector<BehaviourAndWeight> behvaiours, float acceleration, float angularAcceleration)
	: behaviours_(behvaiours), maxAcceleration_(acceleration), maxAngularAcceleration_(angularAcceleration)
{
}

SteeringOutput BlendedSteering::getSteering() const
{
	SteeringOutput result{};

	for (auto& bw : behaviours_)
		result += bw.Weight * std::visit([](auto&& elem){ return elem.getSteering(); }, bw.Behaviour);

	if (result.Linear.length() > maxAcceleration_)
	{
		glm::normalize(result.Linear);
		result.Linear *= maxAcceleration_;
	}

	float angularAcceleration = std::abs(result.Angular);
	if (angularAcceleration > maxAngularAcceleration_)
	{
		result.Angular /= angularAcceleration;
		result.Angular *= maxAngularAcceleration_;
	}

	return result;
}

glm::vec3 BlendedSteering::getTargetPosition() const
{
	return std::visit([](auto& b) { return b.getTargetPosition(); }, behaviours_[0].Behaviour);
}
