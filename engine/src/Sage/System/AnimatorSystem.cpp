#include "AnimatorSystem.h"
#include "Sage/renderer/renderer.hpp"

namespace Sage {
	void AnimatorSystem::RenderFrame(AnimatorComponent& animation, SpriteRendererComponent& sprite, TransformComponent& transform)
	{
		if (!sprite.texture)
			return;

		int frameWidth = sprite.texture->getWidth() / animation.SheetGrid.x;
		int frameHeight = sprite.texture->getHeight() / animation.SheetGrid.y;

		Vec4<int> frameDimensions;
		int currentColumn = animation.CurrentFrame % animation.SheetGrid.x;
		int currentRow = animation.CurrentFrame / animation.SheetGrid.x;
		frameDimensions.x = currentColumn * frameWidth;
		frameDimensions.y = currentRow * frameHeight;

		frameDimensions.w = frameWidth;
		frameDimensions.h = frameHeight;
		Transform t;
		t.Position = transform.Position;
		t.Scale = transform.Scale;
		t.Rotation = transform.Rotation;
		Renderer::RenderRotatedTexture(sprite.texture.get(), frameDimensions, t, sprite.Color);
	}

	void AnimatorSystem::MoveToNextFrame(AnimatorComponent& animation, int frames)
	{
		animation.CurrentFrame = (animation.CurrentFrame + frames) % 
			(animation.SheetGrid.x * animation.SheetGrid.y);
	}
}