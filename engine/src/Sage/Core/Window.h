#pragma once
#include <cinttypes>
#include <memory>
#include <string>
#include <functional>

#include "Sage/Events/Event.h"

namespace Sage {
	struct WindowProperties
	{
		uint32_t width = 0, height = 0;
		std::string name;
	};

	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		static std::unique_ptr<Window> Create(WindowProperties& properties);
		virtual ~Window() = 0;

		virtual uint32_t GetWidth() = 0;
		virtual uint32_t GetHeight() = 0;
		virtual std::string GetName() = 0;
		virtual void SetEventCallback(EventCallbackFn function) = 0;
		virtual void PollEvents() = 0;
	};
}