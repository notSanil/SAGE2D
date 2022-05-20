#pragma once
#include <string>

namespace Sage {
#define BIT(x) 1 << x
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication =	BIT(0),
		EventCategoryKeyboard =		BIT(1),
		EventCategoryMouse =		BIT(2),
		EventCategoryMouseButton =	BIT(3),
		EventCategoryInput =		BIT(4)
	};

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowUnfocus, WindowMoved,
		KeyPressed, KeyReleased, KeyTyped,
		MouseMoved, MouseButtonPressed, MouseButtonReleased, MouseScrolled
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class Event
	{
	public:
		virtual ~Event() = default;
		virtual int GetCategoryFlags() const = 0;
		virtual EventType GetEventType() const = 0;
		bool IsInCategory(EventCategory category) const
		{
			return GetCategoryFlags() & category;
		}

		virtual const char* GetName() const = 0;
		virtual std::string ToString() const { return GetName(); }
	};

	class Dispatcher
	{
	public:
		Dispatcher(Event& e):
			event(e)
		{}

		template<typename T, typename F>
		void Dispatch(const F& func)
		{
			if (event.GetEventType() == T::GetStaticType())
			{
				func(static_cast<T&>(event));
			}
		}

	private:
		Event& event;
	};
}