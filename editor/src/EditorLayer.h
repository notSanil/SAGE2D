#pragma once
#include <Sage/Sage.h>


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
		std::unique_ptr<Texture> alienTexture;
		std::unique_ptr<Texture> whiteTexture;
		Animator animator = Animator("assets/images/alien.png");
		Vec2 viewportSize;
	};
}