#include "EditorLayer.h"
#include <entt.hpp>
#include "Sage/System/AnimatorSystem.h"

namespace Sage {
	EditorLayer::EditorLayer()
	{
		Window& window = Engine::Get().GetWindow();
		frameBuffer = Sage::Framebuffer::Create(window.GetWidth(), window.GetHeight());
		Entity alienEntity = mainScene.CreateEntity();
		alienEntity.GetComponent<NameComponent>().Name = "Burger";
		SpriteRendererComponent& src = alienEntity.AddComponent<SpriteRendererComponent>();
		src.texture = TextureManager::load("assets/images/Burger.png");

		Entity randomEntity = mainScene.CreateEntity();
		randomEntity.GetComponent<NameComponent>().Name = "Random";
		
		auto& animator = randomEntity.AddComponent<AnimatorComponent>();
		animator.SheetGrid = { 6, 4 };
		auto& sprite = randomEntity.AddComponent<SpriteRendererComponent>();
		sprite.texture = TextureManager::load("assets/images/alien.png");
		entityPanel = EntityPanel(&mainScene);

		mainScene.CreateEntity();
	}

	EditorLayer::~EditorLayer()
	{

	}

	void EditorLayer::OnStep(float dt)
	{
		if (viewportSize.x > 0.0f && viewportSize.y > 0.0f && // zero sized framebuffer is invalid
			(frameBuffer->GetWidth() != viewportSize.x || frameBuffer->GetHeight() != viewportSize.y))
		{
			frameBuffer->Resize((uint32_t)viewportSize.x, (uint32_t)viewportSize.y);
		}
	}

	void EditorLayer::OnRender()
	{
		frameBuffer->Bind();
		Renderer::StartScene();
		mainScene.OnRender();
		frameBuffer->Unbind();
	}

	void EditorLayer::OnImGuiRender()
	{
		static bool opt_padding = false;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", NULL, window_flags);
		ImGui::PopStyleVar(3);

		// Submit the DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f));
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Options"))
			{
				Window& window = Engine::Get().GetWindow();
				if (ImGui::MenuItem("Fullscreen", NULL, window.IsFullscreen())) 
				{
					window.SetFullscreen(!window.IsFullscreen());
				}
				ImGui::Separator();
				if (ImGui::MenuItem("Exit"))
				{
					Engine::Get().Shutdown();
				}
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		ImGui::End();
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("Viewport");
		ImGui::PopStyleVar();
		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		
		viewportSize = { viewportPanelSize.x, viewportPanelSize.y };
		
		ImGui::Image(frameBuffer->GetTextureId(), ImVec2{ (float)viewportSize.x, (float)viewportSize.y });
		ImGui::End();
		entityPanel.OnImGuiRender();
		//ImGui::ShowDemoWindow();
	}

	void EditorLayer::OnEvent(Event& e)
	{
	}

}