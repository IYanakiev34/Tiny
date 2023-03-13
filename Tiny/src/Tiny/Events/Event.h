#pragma once

#include <string>
#include <sstream>
#include <functional>
#include <iostream>

#include "Tiny/Core.h"

namespace Tiny
{

	enum class EventType
	{
		None = 0,
		WindowResized, WindowFocus, WindowLostFocus, WindowClose, WindowMoved,
		AppTick, AppRender, AppUpdate,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EApplicationC = BIT(0),
		EInputC = BIT(1),
		EKeyboardC = BIT(2),
		EMouseC = BIT(3),
		EMouseButtonC = BIT(4)
	};


#define EVENT_CLASS_TYPE(type)	static EventType GetStaticType() {return EventType::type;} \
								virtual EventType GetEventType() const override {return GetStaticType();} \
								virtual const char* GetName() const override { return #type; }
#define EVENT_CLASS_CATEGORY(category) virtual int GetEventFlags() const override {return category;}

	class Event
	{
	public:
		virtual ~Event() = default;
		bool b_Handled = false;
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetEventFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		bool IsInCategory(EventCategory category) { return GetEventFlags() & category; }
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& ev)
			: d_event(ev)
		{
		}

		template <typename EventType,typename Func>
		bool Dispatch(Func const &func)
		{
			if (d_event.GetEventType() == EventType::GetStaticType())
			{
				d_event.b_Handled |= func(static_cast<EventType&>(d_event));
				return true;
			}
			return false;
		}

	private:
		Event& d_event;
	};

	inline std::ostream& operator<<(std::ostream& out, Event const& ev)
	{
		return out << ev.ToString();
	}
}

