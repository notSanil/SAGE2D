#pragma once
#include "Sage/gameScene/Entity.h"

namespace Sage {
	class GameScene;

	class NativeScript
	{
	public:
		NativeScript() = default;
		virtual ~NativeScript() = default;
	protected:
		virtual void OnCreate() {};
		virtual void OnStep(float dt) {};
		virtual void OnRender() {};
	protected:
		Entity entity;
		friend class GameScene;
	};
}