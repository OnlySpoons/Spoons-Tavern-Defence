#pragma once
#include <iostream>

#include "Event.h"
#include "EventType.h"

namespace spty {
	
	template<typename T>
	class Observer
	{
	public:
		virtual void handle( Event<T>& e) = 0;
	};

	class TestObserver : public Observer<EventType>
	{
	public:
		void handle(Event<EventType>& e) override
		{
			if (e.type() == EventType::InvalidEvent)
			{
				std::cout << std::boolalpha << e.getName() << " of type InvalidEvent is handled: " << e.isHandled() << std::endl;
			}

			e.handle();
		}
	};
}