#pragma once
#include "Sage/gameScene/Components.h"


namespace Sage {
	class AnimatorSystem
	{
	public:
		static void RenderFrame(AnimatorComponent& animation, SpriteRendererComponent& sprite, TransformComponent& transform);
		static void MoveToNextFrame(AnimatorComponent& animation, int frames = 1);
	};
}