#pragma once
#include "Event.h"

namespace Sage {
	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		EVENT_CLASS_TYPE(WindowClose)
	};

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(uint32_t width, uint32_t height) : 
			width(width), height(height)
		{}

		uint32_t GetWidth() const { return width; }
		uint32_t GetHeight() const { return height; }


		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		EVENT_CLASS_TYPE(WindowResize)

	private:
		uint32_t width, height;
	};
}