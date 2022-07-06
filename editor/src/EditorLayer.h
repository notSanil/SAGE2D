#pragma once
#include <Sage/Sage.h>
#include "Panels/EntityPanel.h"
#include "Panels/BrowserPanel.h"
#include "EditorCameraController.h"

namespace Sage {
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer();
		virtual void OnStep(float dt) override;
		virtual void OnRender() override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event & e) override;

	private:
		void RenderMenu();

	private:
		std::unique_ptr<Framebuffer> frameBuffer;
		std::unique_ptr<GameScene> mainScene;
		glm::vec2 viewportSize;
		EditorCameraController cameraController;

		EntityPanel entityPanel;
		BrowserPanel browserPanel;
		bool entityPanelVisible = true;
		bool browserPanelVisible = true;

		bool viewportHovered = false;
		bool viewportFocused = false;

		std::unique_ptr<Texture> background = nullptr;
	};
}