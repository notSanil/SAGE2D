#pragma once
#include "Event.h"
#include "Sage/Core/MouseCodes.h"

namespace Sage {
	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y):
			mouseX(x), mouseY(y)
		{}

		float GetMouseX() const { return mouseX; }
		float GetMouseY() const { return mouseY; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse)
		EVENT_CLASS_TYPE(MouseMoved)

	private:
		float mouseX, mouseY;
	};

	class MouseScrollEvent : public Event
	{
	public:
		MouseScrollEvent(float x, float y) :
			xOffset(x), yOffset(y)
		{}

		float GetXOffset() const { return xOffset; }
		float GetYOffset() const { return yOffset; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse)
		EVENT_CLASS_TYPE(MouseScrolled)
	private:
		float xOffset, yOffset;
	};

	class MouseButtonEvent : public Event
	{
	public:
		MouseCode GetMouseButton() const { return mouseButton; }
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryMouseButton)

	protected:
		MouseButtonEvent(MouseCode button) :
			mouseButton(button)
		{}

		MouseCode mouseButton;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(MouseCode button):
			MouseButtonEvent(button)
		{}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(MouseCode button) :
			MouseButtonEvent(button)
		{}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}