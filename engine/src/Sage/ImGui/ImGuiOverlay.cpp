#include "ImGuiOverlay.h"

#include <SDL.h>
#include "Sage/engine.hpp"
#include "Platform/Windows/WindowsWindow.h"
#include <backends/imgui_impl_sdl.h>
#include <backends/imgui_impl_opengl3.h>
#include "Sage/Core/Log.h"
#include <glad/glad.h>

namespace Sage {
	ImGuiOverlay::ImGuiOverlay()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		ImGui::StyleColorsDark();
		SDL_Window* window = (SDL_Window*)(Engine::Get().window->GetNativeWindow());
		const char* glsl_version = "#version 330";

		ImGui_ImplSDL2_InitForOpenGL(window, ((WindowsWindow*)Engine::Get().window.get())->glContext);
		ImGui_ImplOpenGL3_Init(glsl_version);
	}

	ImGuiOverlay::~ImGuiOverlay()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiOverlay::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiOverlay::End()
	{
		ImGui::Render();
		ImGuiIO& io = ImGui::GetIO();
		glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
		//glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
		//glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}
	}
}