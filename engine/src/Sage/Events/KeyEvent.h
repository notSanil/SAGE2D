#pragma once
#include "Event.h"
#include "Sage/Core/Keycodes.h"

namespace Sage{
	class KeyEvent : public Event 
	{
	public:
		KeyCode GetKeyCode() const { return keyCode; }
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		KeyEvent(KeyCode keyCode) : keyCode(keyCode)
		{}
		KeyCode keyCode;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(KeyCode keyCode, uint32_t repeatCount) :
			KeyEvent(keyCode), repeatCount(repeatCount) 
		{}

		EVENT_CLASS_TYPE(KeyPressed)

		uint32_t GetRepeatCount() const { return repeatCount; }

	private:
		uint32_t repeatCount;
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(KeyCode keyCode)
			: KeyEvent(keyCode)
		{}

		EVENT_CLASS_TYPE(KeyReleased)
	};
}