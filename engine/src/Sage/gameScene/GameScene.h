#pragma once

#include <entt.hpp>

namespace Sage {
	class Entity;
	class EntityPanel;
	class GameScene
	{
	public:
		GameScene();
		Entity CreateEntity();
		void DestroyEntity(Entity entity);

		void OnRender();
	private:
		entt::registry registry;

		friend class Entity;
		friend class EntityPanel;
	};
}