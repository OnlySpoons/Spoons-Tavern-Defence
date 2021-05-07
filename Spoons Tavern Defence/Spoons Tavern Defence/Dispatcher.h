#pragma once
/*
Group Name: OnlySpoons

Members: Martin Harvey(B00329330), Thomas Cole(B00269678) & Harry Durham(B00347454)

We declare that the following code was produced by OnlySpoons as a group assignment for the CGT Group Project module and that it is our own work.

We are aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.
*/
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

	//Variables
	private:
		static std::map< T, std::vector< EventFunc > > observers_;

	//Functions
	public:

		static void subscribe(const T& type, EventFunc func)
		{
			observers_[type].emplace_back(func);
		}

		static void post(Event<T>& event)
		{
			if (event.isHandled()) return;

			auto type = event.type();

			//Ignore events for which we do not have any observers.
			if (observers_.find(type) == observers_.end()) return;

			for (auto&& observer : observers_.at(type))
			{
				observer(event);
				if (event.isHandled()) return;
			}
		}

	};
}