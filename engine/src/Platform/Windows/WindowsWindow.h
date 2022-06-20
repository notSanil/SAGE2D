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

		void* GetNativeWindow() { return windowData.windowContext; }

		virtual void Update() override;
	private:
		void InitSDL();
		WindowData windowData;
		SDL_GLContext glContext;
		EventCallbackFn eventCallback;
		friend class SdlRenderer;
		friend class ImGuiOverlay;
	};
}