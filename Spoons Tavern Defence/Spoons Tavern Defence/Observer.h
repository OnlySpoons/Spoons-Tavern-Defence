#pragma once
#include <iostream>

#include "Event.h"
#include "EventType.h"

namespace Spoonity {
	
	template<typename T>
	class Observer
	{
	public:
		virtual void handle(const Event<T>& e) = 0;
	};

	class TestObserver : public Observer<EventType>
	{
	public:
		void handle(const Event<EventType>& e) override
		{
			if (e.type() == EventType::InvalidEvent)
			{
				std::cout << std::boolalpha << e.getName() << " of type InvalidEvent is handled: " << e.isHandled() << std::endl;
			}
		}
	};
}