#include "ImGuiOverlay.h"

#include <SDL.h>
#include "Sage/engine.hpp"
#include "Platform/Windows/WindowsWindow.h"
#include "Platform/SDL/SdlRenderer.h"
#include <backends/imgui_impl_sdl.h>
#include <backends/imgui_impl_sdlrenderer.h>
#include "Sage/Core/Log.h"

namespace Sage {
	ImGuiOverlay::ImGuiOverlay()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		ImGui::StyleColorsDark();
		SDL_Window* window = ((WindowsWindow*)Engine::Get().window.get())->GetNativeWindow();

		ImGui_ImplSDL2_InitForSDLRenderer(window, SdlRenderer::GetSDLRenderer());
		ImGui_ImplSDLRenderer_Init(SdlRenderer::GetSDLRenderer());
	}

	ImGuiOverlay::~ImGuiOverlay()
	{
		ImGui_ImplSDLRenderer_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiOverlay::Begin()
	{
		ImGui_ImplSDLRenderer_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiOverlay::End()
	{
		ImGui::Render();
		SDL_SetRenderDrawColor(SdlRenderer::GetSDLRenderer(), (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255), (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255));
		SDL_RenderClear(SdlRenderer::GetSDLRenderer());
		ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}
		//SDL_RenderPresent(SdlRenderer::GetSDLRenderer());
	}
}