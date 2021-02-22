#pragma once
#include <map>
#include <vector>
#include <functional>

#include "Event.h"
#include "EventType.h"
#include "Observer.h"

namespace Spoonity {
	
	template<typename T>
	using SlotType = std::function< void( const Event<T>& ) >;
	//TODO:: make dispatcher static

	template<typename T>
	class Dispatcher
	{
	public:

	private:
		std::map< T, std::vector<SlotType<T>> > _Observers;

		//TODO:: add event queue which is handled at the start/end of each frame

	public:

		void subscribe(const T& type, SlotType<T>& func)
		{
			_Observers[type].push_back(func);
		}

		template<typename ObserverType>
		void subscribe(const T& type, ObserverType& observer)
		{
			SlotType<T> func = std::bind(&ObserverType::handle, observer, std::placeholders::_1);

			_Observers[type].push_back(func);
		}

		void post(const Event<T>& event) const
		{
			auto type = event.type();

			//Ignore events for which we do not have any observers.
			if (_Observers.find(type) == _Observers.end())
				return;

			for (auto&& observer : _Observers.at(type))
				if (!event.isHandled()) observer(event);
		}

	};
}