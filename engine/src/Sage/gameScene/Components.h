#pragma once
#include <memory>
#include "Sage/texture/Texture.hpp"
#include "Sage/transform/point.hpp"
#include "Sage/transform/Vec4.h"

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
		Vec4<int> Color{255, 255, 255, 255};
		Primitives primitive = None;
	};

	struct TransformComponent
	{
		TransformComponent() = default;
		TransformComponent(int x, int y)
			: Position{ x, y }
		{}
		Vec2<int> Position{ 0, 0 };
		Vec2<float> Scale{ 1, 1 };
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
		Vec2<int> SheetGrid{ 1, 1 };
		int Speed = 1;
		int CurrentFrame = 0;
	};
}