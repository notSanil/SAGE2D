#pragma once
#include <string>

#include <memory>
#include <Sage/Core/Window.h>
#include "Sage/Events/Event.h"
#include "Sage/Events/ApplicationEvent.h"
#include "Sage/Core/Timer.h"
#include "Sage/ImGui/ImGuiOverlay.h"
#include "Sage/Core/Layer.h"

namespace Sage {
	class Engine
	{
	public:
		Engine(uint32_t width, uint32_t height, const std::string& name);
		~Engine();

		static Engine& Get() { return *instance; }
		Window& GetWindow() { return *window; }

		void run();
		void PushLayer(std::unique_ptr<Layer> layer);
		void Shutdown() { running = false; };

	private:
		void EventCallback(Event& e);
		void WindowCloseEventCallback(Sage::WindowCloseEvent& e);

	private:
		std::vector<std::unique_ptr<Layer>> layerStack;

		static Engine* instance;

		std::unique_ptr<Window> window;
		bool running = true;
		const int targetFrameRate = 60;
		const float timePerFrame = 1.0f / targetFrameRate;

		Sage::Timer timer;
		std::unique_ptr<ImGuiOverlay> ImGuiOverlay;

		friend class Sage::ImGuiOverlay;
	};
}