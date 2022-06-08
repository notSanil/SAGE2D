#include "AnimatorSystem.h"
#include "Sage/renderer/renderer.hpp"

namespace Sage {
	void AnimatorSystem::RenderFrame(AnimatorComponent& animation, SpriteRendererComponent& sprite, TransformComponent& transform)
	{
		if (!sprite.texture)
			return;

		int frameWidth = sprite.texture->getWidth() / animation.SheetGrid.x;
		int frameHeight = sprite.texture->getHeight() / animation.SheetGrid.y;

		glm::ivec4 frameDimensions;
		int currentColumn = animation.CurrentFrame % animation.SheetGrid.x;
		int currentRow = animation.CurrentFrame / animation.SheetGrid.x;
		frameDimensions.x = currentColumn * frameWidth;
		frameDimensions.y = currentRow * frameHeight;

		frameDimensions.z = frameWidth;
		frameDimensions.w = frameHeight;
		
		glm::imat3x2 t;
		t[0] = transform.Position;
		t[1] = transform.Scale;
		t[2][0] = transform.Rotation;
		//FIXME: Rotation is a float whereas this matrix is an int mat
		Renderer::RenderRotatedTexture(sprite.texture.get(), frameDimensions, t, sprite.Color);
	}

	void AnimatorSystem::MoveToNextFrame(AnimatorComponent& animation, int frames)
	{
		animation.CurrentFrame = (animation.CurrentFrame + frames) % 
			(animation.SheetGrid.x * animation.SheetGrid.y);
	}
}