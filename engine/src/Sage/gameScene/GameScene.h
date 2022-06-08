#pragma once

#include <entt.hpp>
#include <memory>
#include "Sage/texture/Texture.hpp"

namespace Sage {
	class Entity;
	class EntityPanel;
	class GameScene
	{
	public:
		GameScene();
		Entity CreateEntity(uint32_t id);
		Entity CreateEntity();
		void DestroyEntity(Entity entity);

		void OnRender();
	private:
		entt::registry registry;

		friend class Entity;
		friend class EntityPanel;
	};
}