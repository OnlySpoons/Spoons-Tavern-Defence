#pragma once
/*
Group Name: OnlySpoons

Members: Martin Harvey(B00329330), Thomas Cole(B00269678) & Harry Durham(B00347454)

We declare that the following code was produced by OnlySpoons as a group assignment for the CGT Group Project module and that it is our own work.

We are aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.
*/
#include <glm/glm.hpp>

struct SteeringOutput
{
	glm::vec3 Linear;
	float Angular;

	SteeringOutput& operator+=(const SteeringOutput& rhs)
	{
		Linear += rhs.Linear;
		Angular += rhs.Angular;
		return *this;
	}

	friend SteeringOutput operator*(const float lhs, const SteeringOutput& y)
	{
		return { lhs * y.Linear, lhs * y.Angular };
	}
};