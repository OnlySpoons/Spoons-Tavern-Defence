#pragma once
/*
Group Name: OnlySpoons

Members: Martin Harvey(B00329330), Thomas Cole(B00269678) & Harry Durham(B00347454)

We declare that the following code was produced by OnlySpoons as a group assignment for the CGT Group Project module and that it is our own work.

We are aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.
*/
#include <glm/fwd.hpp>
#include <glm/gtx/transform.hpp>

struct WorldDir
{
	//Constexprs for the cardinal direction vectors
	static constexpr glm::vec3 UP = glm::vec3(0.0f, 1.0f, 0.0f);
	static constexpr glm::vec3 RIGHT = glm::vec3(1.0f, 0.0f, 0.0f);
	static constexpr glm::vec3 FRONT = glm::vec3(0.0f, 0.0f, 1.0f);

	static constexpr glm::vec3 DOWN = -UP;
	static constexpr glm::vec3 LEFT = -RIGHT;
	static constexpr glm::vec3 BACK = -FRONT;
};