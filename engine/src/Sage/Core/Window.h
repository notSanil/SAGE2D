#pragma once
#include <cinttypes>
#include <memory>
#include <string>
#include <functional>

#include "Sage/Events/Event.h"

namespace Sage {
	struct WindowProperties
	{
		bool isFullscreen = false;
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
		virtual void SetFullscreen(bool fullscreen) = 0;
		virtual bool IsFullscreen() = 0;
		virtual void* GetNativeWindow() = 0;

		virtual void Update() = 0;
	};
}