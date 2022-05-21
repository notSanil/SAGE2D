#pragma once
#include "Sage/Events/Event.h"

namespace Sage {
	class Layer
	{
	public:
		virtual ~Layer() = default;
		virtual void OnStep(float dt) = 0;
		virtual void OnRender() = 0;
		virtual void OnImGuiRender() = 0;
		virtual void OnEvent(Event& e) = 0;
	};
}