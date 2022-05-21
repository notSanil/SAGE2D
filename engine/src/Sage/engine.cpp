#include "engine.hpp"

#include <functional>

#include "Sage/renderer/renderer.hpp"
#include "Sage/gameScene/sceneManager.hpp"
#include "Sage/texture/texture.hpp"
#include "Sage/Core/Log.h"
#include <imgui.h>

Engine::Engine(uint32_t width, uint32_t height, const std::string &name)
{
	instance = this;
	Sage::Log::Init();

	Sage::WindowProperties properties{ width, height, name };
	window = Sage::Window::Create(properties);
	window->SetEventCallback(std::bind(&Engine::EventCallback, this, std::placeholders::_1));

	Renderer::init(window.get());
	timer.Reset();

	ImGuiOverlay = new Sage::ImGuiOverlay();
}

void Engine::EventCallback(Sage::Event& e)
{
	Sage::Dispatcher dispatcher(e);
	dispatcher.Dispatch<Sage::WindowCloseEvent>(std::bind(&Engine::WindowCloseEventCallback, this, std::placeholders::_1));
	sceneManager::getCurrentScene()->on_event(e);
}

void Engine::WindowCloseEventCallback(Sage::WindowCloseEvent& e)
{
	running = false;
}

Engine::~Engine()
{
	sceneManager::quit();
	Renderer::destroy();
	//Font::freeAllFonts();
}

void Engine::run()
{
	while (running)
	{
		window->PollEvents();
		float deltaTime = timer.Elapsed();
		timer.Reset();

		sceneManager::getCurrentScene()->on_step(deltaTime);
		sceneManager::getCurrentScene()->on_render();
		ImGuiOverlay->Begin();
		bool open = true;
		//ImGui::ShowDemoWindow(&open);
		ImGui::Begin("Test");
		std::shared_ptr<Sage::Texture> tex = Sage::TextureManager::load("assets/images/alien.png");
		ImGui::Image(tex->GetRendererID(), ImVec2{100.0f, 100.0f});
		ImGui::End();
		ImGuiOverlay->End();

		Renderer::EndScene();

	}
}

Engine* Engine::instance = nullptr;

