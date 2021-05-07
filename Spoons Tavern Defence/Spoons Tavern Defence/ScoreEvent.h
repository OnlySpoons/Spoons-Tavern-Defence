#pragma once
/*
Group Name: OnlySpoons

Members: Martin Harvey(B00329330), Thomas Cole(B00269678) & Harry Durham(B00347454)

We declare that the following code was produced by OnlySpoons as a group assignment for the CGT Group Project module and that it is our own work.

We are aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.
*/
#include "Event.h"
#include "GameEventType.h"

class ScoreEvent : public spty::Event<GameEventType>
{
public:
	static constexpr GameEventType Type = GameEventType::ScoreEvent;

//Variables
public:
	int amount;

//Functions
public:
	//Constructor
	ScoreEvent(int amount)
		: spty::Event<GameEventType>(Type, "ScoreEvent"),
		amount(amount)
	{
	}
};