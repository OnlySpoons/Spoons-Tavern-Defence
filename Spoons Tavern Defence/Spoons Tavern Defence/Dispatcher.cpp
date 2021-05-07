#include "Dispatcher.h"
#include "EventType.h"
#include "GameEventType.h"	

namespace spty {
	using EngineDispatcher = Dispatcher< EventType >;
	std::map < EventType, std::vector< EngineDispatcher::EventFunc > > EngineDispatcher::observers_;
}
	using GameDispatcher = spty::Dispatcher<GameEventType>;
	std::map< GameEventType, std::vector< GameDispatcher::EventFunc > > GameDispatcher::observers_;