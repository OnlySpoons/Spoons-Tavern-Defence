#pragma once
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