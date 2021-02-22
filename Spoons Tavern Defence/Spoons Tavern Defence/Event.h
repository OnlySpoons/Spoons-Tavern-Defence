#pragma once
#include <string>

#include "EventType.h"

namespace Spoonity {

	template<typename T>
	class Event
	{
	protected:
		T _Type;
		std::string _Name;
		bool _Handled = false;

	public:
		Event() {}

		Event(T type, const std::string& name = "") : _Type(type), _Name(name) {}

		virtual ~Event() {}

		inline const T type() const { return _Type; };
		inline const std::string& getName() const { return _Name; };
		virtual bool isHandled() const { return _Handled; };
	};

	class TestEvent : public Event<EventType>
	{
	public:

		static constexpr EventType Type = EventType::InvalidEvent;

		TestEvent() :Event<EventType>(EventType::InvalidEvent, "TestEvent") {};
		
		virtual ~TestEvent() {}
	};
}