#pragma once
#include "point.hpp"

namespace Sage {
	struct Transform
	{
		Vec2<int> Position;
		Vec2<float> Scale;
		float Rotation;
	};
}