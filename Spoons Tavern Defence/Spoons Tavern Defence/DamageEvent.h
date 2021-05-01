#pragma once
#include "bullet/btBulletDynamicsCommon.h"

#include "Event.h"
#include "GameEventType.h"

class DamageEvent : public spty::Event<GameEventType>
{
public:

	static constexpr GameEventType Type = GameEventType::DamageEvent;

	DamageEvent(const btCollisionObject* target, int amount)
		: spty::Event<GameEventType>(Type, "DamageEvent"),
		target(btRigidBody::upcast(target)), amount(amount)
	{
	}

	virtual ~DamageEvent() { target = nullptr; }

	int amount;

	const btRigidBody* target;
};