#pragma once

#include <entt.hpp>
#include <memory>
#include "Sage/texture/Texture.hpp"

namespace Sage {
	class Entity;
	class EntityPanel;
	class Serialiser;
	class GameScene
	{
	public:
		GameScene();
		GameScene(const std::string& sceneName);
		Entity CreateEntity(uint32_t id);
		Entity CreateEntity();
		void DestroyEntity(Entity entity);

		const std::string& GetName() { return name; }
		void SetName(const std::string& newName) { name = newName; }

		void OnRender();
	private:
		entt::registry registry;
		std::string name;

		friend class Entity;
		friend class EntityPanel;
		friend class Serialiser;
	};
}