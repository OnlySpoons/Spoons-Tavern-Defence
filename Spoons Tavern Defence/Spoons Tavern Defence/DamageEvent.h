#pragma once
/*
Group Name: OnlySpoons

Members: Martin Harvey(B00329330), Thomas Cole(B00269678) & Harry Durham(B00347454)

We declare that the following code was produced by OnlySpoons as a group assignment for the CGT Group Project module and that it is our own work.

We are aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.
*/
#include <glm/ext/vector_float3.hpp>
#include <bullet/btBulletDynamicsCommon.h>

#include "Event.h"
#include "GameEventType.h"

class DamageEvent : public spty::Event<GameEventType>
{
public:
	static constexpr GameEventType Type = GameEventType::DamageEvent;

//Variables
public:
	int amount;
	const btRigidBody* target;
	glm::vec3 direction;

//Functions
public:
	//Constructor
	DamageEvent(const btCollisionObject* target, int amount, glm::vec3 damageDir) 
		: spty::Event<GameEventType>(Type, "DamageEvent"),
		target(btRigidBody::upcast(target)), amount(amount), direction(damageDir)
	{
	}

	//Destructor
	virtual ~DamageEvent() { target = nullptr; }
};