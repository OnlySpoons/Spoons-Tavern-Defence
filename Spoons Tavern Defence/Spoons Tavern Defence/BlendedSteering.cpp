#include "BlendedSteering.h"

BlendedSteering::BlendedSteering(std::vector<BehaviourAndWeight> behvaiours, float acceleration, float angularAcceleration)
	: _behaviours(behvaiours), _maxAcceleration(acceleration), _maxAngularAcceleration(angularAcceleration)
{
}

SteeringOutput BlendedSteering::getSteering() const
{
	SteeringOutput result{};

	for (auto& bw : _behaviours)
		result += bw._weight * std::visit([](auto& b) { return b.getSteering(); }, bw._behaviour);

	if (result._linear.length() > _maxAcceleration)
	{
		glm::normalize(result._linear);
		result._linear *= _maxAcceleration;
	}

	float angularAcceleration = std::abs(result._angular);
	if (angularAcceleration > _maxAngularAcceleration)
	{
		result._angular /= angularAcceleration;
		result._angular *= _maxAngularAcceleration;
	}

	return result;
	
}

glm::vec3 BlendedSteering::getTargetPosition() const
{
	return std::visit([](auto& b) { return b.getTargetPosition(); }, _behaviours[0]._behaviour);
}
