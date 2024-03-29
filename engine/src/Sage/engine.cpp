#include "engine.hpp"
#include <functional>
#include "Sage/renderer/renderer.hpp"
#include "Sage/texture/texture.hpp"
#include "Sage/Core/Log.h"
#include "Sage/Core/Input.h"
#include "Sage/Scripting/ScriptEngine.h"

namespace Sage {
	Engine::Engine(uint32_t width, uint32_t height, const std::string& name)
	{
		instance = this;
		Sage::Log::Init();

		Sage::WindowProperties properties{ true, width, height, name };
		window = Sage::Window::Create(properties);
		window->SetEventCallback(std::bind(&Engine::EventCallback, this, std::placeholders::_1));

		Renderer::init(window.get());
		timer.Reset();
		ScriptEngine::Init();

		ImGuiOverlay = std::make_unique<Sage::ImGuiOverlay>();
	}

	void Engine::EventCallback(Sage::Event& e)
	{
		Sage::Dispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Engine::WindowCloseEventCallback, this, std::placeholders::_1));

		dispatcher.Dispatch<KeyPressedEvent>(std::bind((void(*)(KeyPressedEvent&))&Input::OnKeyPressed, std::placeholders::_1));
		dispatcher.Dispatch<KeyReleasedEvent>(std::bind((void(*)(KeyReleasedEvent&)) & Input::OnKeyReleased, std::placeholders::_1));
		dispatcher.Dispatch<MouseButtonPressedEvent>(std::bind((void(*)(MouseButtonPressedEvent&)) &Input::OnMouseButtonPressed, std::placeholders::_1));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(std::bind((void(*)(MouseButtonReleasedEvent&)) &Input::OnMouseButtonReleased, std::placeholders::_1));

		for (const auto& layer : layerStack)
		{
			layer->OnEvent(e);
		}
	}

	void Engine::WindowCloseEventCallback(WindowCloseEvent& e)
	{
		running = false;
	}

	Engine::~Engine()
	{
		Renderer::destroy();
		ScriptEngine::Destroy();
		//Font::freeAllFonts();
	}

	void Engine::run()
	{
		while (running)
		{
			window->PollEvents();

			float deltaTime = timer.Elapsed();
			while (deltaTime < timePerFrame)
				deltaTime = timer.Elapsed();
			timer.Reset();
			for (const auto& layer : layerStack)
			{
				layer->OnStep(deltaTime);
			}

			for (const auto& layer : layerStack)
			{
				layer->OnRender();
			}

			ImGuiOverlay->Begin();
			for (const auto& layer : layerStack)
			{
				layer->OnImGuiRender();
			}
			ImGuiOverlay->End();

			window->Update();
		}
	}
	void Engine::PushLayer(std::unique_ptr<Layer> layer)
	{
		layerStack.push_back(std::move(layer));
	}
	Engine* Engine::instance = nullptr;
}

