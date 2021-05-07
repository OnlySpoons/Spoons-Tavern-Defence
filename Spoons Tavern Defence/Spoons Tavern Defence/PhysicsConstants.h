#pragma once
/*
Group Name: OnlySpoons

Members: Martin Harvey(B00329330), Thomas Cole(B00269678) & Harry Durham(B00347454)

We declare that the following code was produced by OnlySpoons as a group assignment for the CGT Group Project module and that it is our own work.

We are aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.
*/
#include <glm\glm.hpp>

struct PhysicsConstants
{
	static constexpr float GRAVITY = 9.81f * 3;
	static constexpr float FRICTION = 0.6f;
	static constexpr bool KINEMATIC = false;
	static constexpr glm::vec3 CENTRE = glm::vec3(0.0f);
	static constexpr glm::vec3 INERTIA = glm::vec3(0.0f);
	static constexpr glm::vec3 UNIT_CUBE = glm::vec3(1.0f);
};