#include "EditorLayer.h"
#include "Sage/gameScene/Serialiser.h"
#include "Sage/Core/Input.h"
#include "Sage/Scripting/ScriptEngine.h"

namespace Sage {
	EditorLayer::EditorLayer()
	{
		mainScene = std::make_unique<GameScene>("Sample Scene");

		Window& window = Engine::Get().GetWindow();
		frameBuffer = Sage::Framebuffer::Create(window.GetWidth(), window.GetHeight());
		entityPanel = EntityPanel(mainScene.get());

		background = Texture::Create("resources/checkBackground.png", ResizingPolicy::Nearest);

		class moveScript : public NativeScript
		{
		public:
			virtual void OnStep(float dt) 
			{
				float delY = 0.0f;
				constexpr float speed = 2.0f;
				if (Input::IsKeyPressed(KeyCode::Up))
				{
					delY -= speed * dt;
				}
				
				if (Input::IsKeyPressed(KeyCode::Down))
					delY += speed * dt;

				auto& transform = entity.GetComponent<TransformComponent>();
				transform.Position.y += delY;
			};

			virtual void OnRender() 
			{
				auto& transform = entity.GetComponent<TransformComponent>();
				Renderer::RenderRect(transform.Position, { 0.5f * scale, 1.5f * scale }, { 1.0f, 1.0f, 1.0f, 1.0f });
			};
		private:
			const float scale = 0.25f;
		};





		Entity e = mainScene->CreateEntity();
		e.AddComponent<NativeScriptComponent>().Bind<moveScript>();
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
			cameraController.OnWindowResize(viewportSize.x, viewportSize.y);
		}
		if (viewportHovered)
			cameraController.OnStep(dt);

		mainScene->OnStep(dt);
	}

	void EditorLayer::OnRender()
	{
		frameBuffer->Bind();
		Renderer::StartScene(cameraController.GetCamera());
		//Renderer::RenderTexture(background.get(), { 0.0f, 0.0f }, { 1.0f, 1.0f });
		mainScene->OnRender();
		ScriptEngine::ExecuteScript("assets/scripts/test.lua");
		Renderer::EndScene();
		frameBuffer->Unbind();
	}

	void EditorLayer::OnImGuiRender()
	{
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking
			| ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		ImGui::Begin("DockSpace", NULL, window_flags);
		ImGui::PopStyleVar(3);

		// Submit the DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f));
		}
		RenderMenu();
		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("Viewport");
		ImGui::PopStyleVar();

		viewportHovered = ImGui::IsWindowHovered();
		viewportFocused = ImGui::IsWindowFocused();
		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		viewportSize = { viewportPanelSize.x, viewportPanelSize.y };		
		ImGui::Image(frameBuffer->GetTextureId(), ImVec2{ (float)viewportSize.x, (float)viewportSize.y });
		ImGui::End();

		if (entityPanelVisible)
			entityPanel.OnImGuiRender();
		
		if (browserPanelVisible)
			browserPanel.OnImGuiRender();
	}

	void EditorLayer::RenderMenu()
	{
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("New"))
				{
					mainScene = std::make_unique<GameScene>("New Scene");
					entityPanel.SetSceneContext(mainScene.get());
				}

				if (ImGui::MenuItem("Save"))
				{
					Serialiser::SerialiseScene(mainScene.get(), "assets/scenes/mainScene.sge");
				}

				if (ImGui::MenuItem("Open"))
				{
					mainScene = std::make_unique<GameScene>();
					Serialiser::DeserialiseScene("assets/scenes/mainScene.sge", mainScene.get());

					entityPanel.SetSceneContext(mainScene.get());
				}

				ImGui::Separator();
				if (ImGui::MenuItem("Exit"))
				{
					Engine::Get().Shutdown();
				}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("View"))
			{
				if (ImGui::MenuItem("Scene Explorer", nullptr, entityPanelVisible))
				{
					entityPanelVisible = !entityPanelVisible;
				}

				if (ImGui::MenuItem("Browser", nullptr, browserPanelVisible))
				{
					browserPanelVisible = !browserPanelVisible;
				}

				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
	}

	void EditorLayer::OnEvent(Event& e)
	{
		if (viewportHovered)
			cameraController.OnEvent(e);
	}
}