#pragma once
#include "Sage/Core/Window.h"
#include <SDL.h>

namespace Sage {
	struct WindowData
	{
		WindowProperties properties;
		SDL_Window* windowContext;
	};


	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(WindowProperties& properties);
		virtual ~WindowsWindow() override;

		virtual uint32_t GetWidth() override;
		virtual uint32_t GetHeight() override;
		virtual std::string GetName() override;
	private:
		WindowData windowData;

		friend class SdlRenderer;
	};
}