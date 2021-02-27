#pragma once
#include "Event.h"

namespace Spoonity {

	class WindowClosedEvent : public Event<EventType>
	{
	public:

		static constexpr EventType Type = EventType::WindowClosed;

		WindowClosedEvent() :Event<EventType>(EventType::WindowClosed, "WindowClosed") {};

		virtual ~WindowClosedEvent() {}
	};

	class SwapBuffersEvent : public Event<EventType>
	{
	public:

		static constexpr EventType Type = EventType::SwapBuffers;

		SwapBuffersEvent() :Event<EventType>(EventType::SwapBuffers, "SwapBuffers") {};

		virtual ~SwapBuffersEvent() {}
	};
}