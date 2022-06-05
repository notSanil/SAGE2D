#pragma once
#include <Sage/Sage.h>
#include "Panels/EntityPanel.h"
#include "Sage/animator/animator.hpp"

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
		std::unique_ptr<Framebuffer> frameBuffer;
		GameScene mainScene;
		Vec2<float> viewportSize;
		EntityPanel entityPanel;
	};
}