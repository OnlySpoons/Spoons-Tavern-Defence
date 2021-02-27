#include "Dispatcher.h"

namespace Spoonity {

	std::map< EventType, std::vector<EventFunc<EventType>> > Dispatcher<EventType>::_observers;

}