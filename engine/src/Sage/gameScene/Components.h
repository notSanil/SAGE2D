#pragma once
#include <memory>
#include "Sage/texture/Texture.hpp"
#include <glm/glm.hpp>

namespace Sage {
	struct SpriteRendererComponent
	{
		enum Primitives
		{
			None,
			Rectangle,
			COUNT
		};
		std::shared_ptr<Texture> texture = nullptr;
		glm::ivec4 Color{ 255, 255, 255, 255 };
		Primitives primitive = None;
	};

	struct TransformComponent
	{
		TransformComponent() = default;
		TransformComponent(int x, int y)
			: Position{ x, y }
		{}

		operator glm::imat3x2()
		{
			glm::imat3x2 t;
			t[0] = Position;
			t[1] = Scale;
			t[2][0] = Rotation;
			return t;
		}

		glm::ivec2 Position{ 0, 0 };
		glm::vec2 Scale{ 1, 1 };
		float Rotation = 0.0f;
	};

	struct NameComponent
	{
		NameComponent(const std::string& name = "NewEntity")
			: Name(name)
		{}
		std::string Name;
	};

	struct AnimatorComponent
	{
		glm::ivec2 SheetGrid{ 1, 1 };
		int Speed = 1;
		int CurrentFrame = 0;
	};
}