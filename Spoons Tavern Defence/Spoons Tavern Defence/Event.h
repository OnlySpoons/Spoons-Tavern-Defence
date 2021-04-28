#pragma once
#include <string>

#include "EventType.h"

namespace spty {

	template<typename toType, typename fromType>
	toType EventCast( fromType& from ) { return *dynamic_cast< toType* >(&from); }

	template<typename T>
	class Event
	{
	protected:
		T _type;
		std::string _name;
		bool _handled = false;

	public:
		Event() {}

		Event(T type, const std::string& name = "") : _type(type), _name(name) {}

		virtual ~Event() {}

		inline const T type() const { return _type; }
		inline const std::string& getName() const { return _name; }
		virtual bool isHandled() const { return _handled; }
		virtual void handle() { _handled = true; }
	};

	class TestEvent : public Event<EventType>
	{
	public:

		static constexpr EventType Type = EventType::InvalidEvent;

		TestEvent() :Event<EventType>(Type, "TestEvent") {}
		
		virtual ~TestEvent() {}
	};
}