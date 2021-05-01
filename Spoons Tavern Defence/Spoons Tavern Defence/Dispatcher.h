#pragma once
#include <map>
#include <vector>
#include <functional>

#include "Event.h"
#include "EventType.h"
#include "Observer.h"

namespace spty {
	
	template<typename T>
	class Dispatcher
	{
	public:
		using EventFunc = std::function< void( Event<T>& ) >;

	private:
		static std::map< T, std::vector<EventFunc> > _observers;

	public:

		static void subscribe(const T& type, EventFunc func)
		{
			_observers[type].emplace_back(func);
		}

		template<typename ObserverType>
		static void subscribe(const T& type, ObserverType& observer)
		{
			EventFunc func = std::bind(&ObserverType::handle, observer, std::placeholders::_1);

			_observers[type].emplace_back(func);
		}

		static void post(Event<T>& event)
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