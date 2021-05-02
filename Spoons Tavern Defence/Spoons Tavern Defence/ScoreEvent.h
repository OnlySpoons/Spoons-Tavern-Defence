#pragma once

#include "Event.h"
#include "GameEventType.h"

class ScoreEvent : public spty::Event<GameEventType>
{
public:

	static constexpr GameEventType Type = GameEventType::ScoreEvent;

	ScoreEvent(int amount)
		: spty::Event<GameEventType>(Type, "ScoreEvent"),
		amount(amount)
	{
	}

	int amount;
};