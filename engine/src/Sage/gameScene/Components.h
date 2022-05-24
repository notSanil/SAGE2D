#pragma once
#include <memory>
#include "Sage/texture/Texture.hpp"
#include "Sage/transform/point.hpp"
#include "Sage/transform/Vec4.h"

namespace Sage {
	struct SpriteRendererComponent
	{
		std::shared_ptr<Texture> texture;
		Vec4 color{255, 255, 255, 255};
	};

	struct TransformComponent
	{
		TransformComponent() = default;
		TransformComponent(int x, int y)
			: position{ x, y }
		{}
		Point position{ 0, 0 };
		Vec2 Scale{ 1, 1 };
	};

	struct NameComponent
	{
		NameComponent(const std::string& name = "NewEntity")
			: name(name)
		{}
		std::string name;
	};

}