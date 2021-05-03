#pragma once

#include "Event.h"
#include "GameEventType.h"

class PlaySoundEvent : public spty::Event<GameEventType>
{
public:

	static constexpr GameEventType Type = GameEventType::PlaySoundEvent;

	PlaySoundEvent(int id)
		: spty::Event<GameEventType>(Type, "PlaySoundEvent"),
		id(id)
	{
	}

	int id;
};