#pragma once
#include "bullet/btBulletDynamicsCommon.h"

#include "Event.h"
#include "GameEventType.h"

class DamageEvent : public spty::Event<GameEventType>
{
public:

	static constexpr GameEventType Type = GameEventType::DamageEvent;

	DamageEvent(const btRigidBody* target, int amount)
		: spty::Event<GameEventType>(Type, "DamageEvent"),
		target(target), amount(amount)
	{
	}

	virtual ~DamageEvent() { delete target; }

	int amount;

	const btRigidBody* target;
};