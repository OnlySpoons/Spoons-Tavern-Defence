#pragma once
#include <glm/glm.hpp>

struct SteeringOutput
{
	glm::vec3 _linear;
	float _angular;

	SteeringOutput& operator+=(const SteeringOutput& rhs)
	{
		_linear += rhs._linear;
		_angular += rhs._angular;
		return *this;
	}

	friend SteeringOutput operator*(const float lhs, const SteeringOutput& y)
	{
		return { lhs * y._linear, lhs * y._angular };
	}
};