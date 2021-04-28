#include "Dispatcher.h"
#include "EventType.h"
#include "GameEventType.h"	

namespace spty {

	using sptyDispatch = Dispatcher<EventType>;
	std::map < EventType, std::vector< sptyDispatch::EventFunc > >sptyDispatch::_observers;

	using gameDispatch = Dispatcher<GameEventType>;
	std::map<GameEventType, std::vector<gameDispatch::EventFunc> > gameDispatch::_observers;

}