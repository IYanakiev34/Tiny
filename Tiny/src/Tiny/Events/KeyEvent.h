#pragma once

#include "Tiny/Events/Event.h"

namespace Tiny
{
	class KeyEvent : public Event
	{
	public:
		int GetKeyCode() const { return d_keyCode; }
		EVENT_CLASS_CATEGORY(EKeyboardC | EInputC)
	protected:
		// KEY COUDE SHOULD BE ENUM
		KeyEvent(int keyCode)
			: d_keyCode(keyCode)
		{}
		int d_keyCode;
	};


	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keyCode, bool isRepeat = false)
			: KeyEvent(keyCode), b_isRepeat(isRepeat)
		{

		}

		bool IsRepeat() const { return b_isRepeat; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << GetKeyCode() << " (repeat = " << b_isRepeat << ")";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		bool b_isRepeat;
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keyCode)
			: KeyEvent(keyCode)
		{

		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << GetKeyCode();
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)

	};

	class KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keyCode)
			: KeyEvent(keyCode)
		{
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << GetKeyCode();
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};
}