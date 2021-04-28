#pragma once

#include <glm\glm.hpp>

namespace PhysicsConstants
{
	const float GRAVITY = 9.81f * 3;
	const float FRICTION = 0.6f;
	const bool KINEMATIC = false;
	const glm::vec3 CENTRE = glm::vec3(0.0f);
	const glm::vec3 INERTIA = glm::vec3(0.0f);
	const glm::vec3 UNIT_CUBE = glm::vec3(1.0f);

}