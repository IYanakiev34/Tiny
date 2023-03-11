#pragma once

#include "Tiny/Events/Event.h"


namespace Tiny
{
	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y)
			: d_x(x),
			  d_y(y)
		{
		}

		float GetX() const { return d_x; }
		float GetY() const { return d_y; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: X(" << d_x << "), Y(" << d_y << ")";
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EMouseC | EInputC)

	private:
		float d_x;
		float d_y;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float offsetX, float offsetY)
			: d_offsetX(offsetX),
			  d_offsetY(offsetY)
		{}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: offsetX(" << d_offsetX << "), offsetY(" << d_offsetY << ")";
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EInputC | EMouseC)
	private:
		float d_offsetX;
		float d_offsetY;
	};

	class MouseButtonEvent : public Event
	{
	public:
		int GetMouseButton() const { return d_mouseButton;}

		EVENT_CLASS_CATEGORY(EMouseC | EMouseButtonC | EInputC)
	protected:
		MouseButtonEvent(int mouseButton)
			: d_mouseButton(mouseButton)
		{
		}

		int d_mouseButton;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int mouseButtonPressed)
			: MouseButtonEvent(mouseButtonPressed)
		{}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << d_mouseButton;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int mouseButtonReleased)
			: MouseButtonEvent(mouseButtonReleased)
		{}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << d_mouseButton;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}