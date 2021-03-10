#pragma once
#include <map>
#include <vector>
#include <functional>

#include "Event.h"
#include "EventType.h"
#include "Observer.h"

namespace Spoonity {
	
	template<typename T>
	class Dispatcher
	{
	public:
		using EventFunc = std::function< void( Event<T>& ) >;

	private:
		std::map< T, std::vector<EventFunc<T>> > _observers;

		//TODO:: add event queue which is handled at the start/end of each frame

	public:

		void subscribe(const T& type, EventFunc<T>& func)
		{
			_observers[type].push_back(func);
		}

		template<typename ObserverType>
		void subscribe(const T& type, ObserverType& observer)
		{
			EventFunc<T> func = std::bind(&ObserverType::handle, observer, std::placeholders::_1);

			_observers[type].push_back(func);
		}

		void post(Event<T>& event) const
		{
			if (event.isHandled()) return;

			auto type = event.type();

			//Ignore events for which we do not have any observers.
			if (_observers.find(type) == _observers.end())
				return;

			for (auto&& observer : _observers.at(type))
			{
				observer(event);
				if (event.isHandled()) return;
			}
		}

	};
}