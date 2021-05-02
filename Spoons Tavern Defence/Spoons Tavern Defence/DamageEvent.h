#pragma once
#include <glm/ext/vector_float3.hpp>
#include "bullet/btBulletDynamicsCommon.h"

#include "Event.h"
#include "GameEventType.h"

class DamageEvent : public spty::Event<GameEventType>
{
public:

	static constexpr GameEventType Type = GameEventType::DamageEvent;

	DamageEvent(const btCollisionObject* target, int amount, glm::vec3 damageDir)
		: spty::Event<GameEventType>(Type, "DamageEvent"),
		target(btRigidBody::upcast(target)),
		amount(amount), direction(damageDir)
	{
	}

	virtual ~DamageEvent() { target = nullptr; }

	int amount;
	const btRigidBody* target;
	glm::vec3 direction;
};