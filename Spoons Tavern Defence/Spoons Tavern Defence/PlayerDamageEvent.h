#pragma once
#include <glm/ext/vector_float3.hpp>

#include "Event.h"
#include "GameEventType.h"

class PlayerDamageEvent : public spty::Event<GameEventType>
{
public:

	static constexpr GameEventType Type = GameEventType::PlayerDamageEvent;

	PlayerDamageEvent(int amount, glm::vec3 damageDir)
		: spty::Event<GameEventType>(Type, "PlayerDamageEvent"),
		amount(amount), direction(damageDir)
	{
	}

	int amount;
	glm::vec3 direction;
};