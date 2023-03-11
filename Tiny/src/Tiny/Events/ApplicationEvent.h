#pragma once

#include "Tiny/Events/Event.h"

namespace Tiny
{
	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned width, unsigned height)
			: d_width(width),
			  d_height(height)
		{
		}

		unsigned GetWidth() const { return d_width; }
		unsigned GetHeight() const { return d_height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Window Resized Event, width: " << d_width << ", height: " << d_height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResized)
		EVENT_CLASS_CATEGORY(EApplicationC)
	private:
		unsigned d_width;
		unsigned d_height;
	};

	class WindowClosedEvent : public Event
	{
	public:
		WindowClosedEvent() = default;

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EApplicationC)
	};

	// TODO add rest of window events

	class AppTickEvent : public Event
	{
	public:
		AppTickEvent() = default;

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EApplicationC)
	};

	class AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() = default;

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EApplicationC)
	};

	class AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() = default;

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EApplicationC)
	};
}