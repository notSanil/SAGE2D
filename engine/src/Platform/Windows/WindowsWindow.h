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
		virtual void SetEventCallback(EventCallbackFn function) override;
		virtual void PollEvents() override;
		virtual void SetFullscreen(bool fullscreen) override;
		virtual bool IsFullscreen() override { return windowData.properties.isFullscreen; };

		SDL_Window* GetNativeWindow() { return windowData.windowContext; }
	private:
		void InitSDL();
		WindowData windowData;
		EventCallbackFn eventCallback;
		friend class SdlRenderer;
	};
}