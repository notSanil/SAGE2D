#include "AnimatorSystem.h"
#include "Sage/renderer/renderer.hpp"
#include <glm/gtx/matrix_transform_2d.hpp>

namespace Sage {
	void AnimatorSystem::RenderFrame(AnimatorComponent& animation, SpriteRendererComponent& sprite, TransformComponent& transformComponent)
	{
		if (!sprite.texture)
			return;

		float frameWidth = (float)sprite.texture->getWidth() / animation.SheetGrid.x;
		float frameHeight = (float)sprite.texture->getHeight() / animation.SheetGrid.y;

		glm::vec4 frameDimensions;
		int currentColumn = animation.CurrentFrame % animation.SheetGrid.x;
		int currentRow = animation.CurrentFrame / animation.SheetGrid.x;
		frameDimensions.x = (currentColumn * frameWidth) / sprite.texture->getWidth();
		frameDimensions.y = (currentRow * frameHeight) / sprite.texture->getHeight();

		frameDimensions.z = frameWidth / sprite.texture->getWidth();
		frameDimensions.w = frameHeight / sprite.texture->getHeight();

		glm::mat3 transform = glm::translate(glm::mat3(1.0f), transformComponent.Position) *
			glm::rotate(glm::mat3(1.0f), transformComponent.Rotation) *
			glm::scale(glm::mat3(1.0f), transformComponent.Scale);
		
		Renderer::RenderRotatedTexture(sprite.texture.get(), frameDimensions, transform, sprite.Color);
	}

	void AnimatorSystem::MoveToNextFrame(AnimatorComponent& animation, int frames)
	{
		animation.CurrentFrame = (animation.CurrentFrame + frames) % 
			(animation.SheetGrid.x * animation.SheetGrid.y);
	}
}