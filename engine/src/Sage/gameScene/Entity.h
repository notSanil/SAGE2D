#pragma once

#include <entt.hpp>
#include "GameScene.h"
namespace Sage {
	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity id, GameScene* scene);


		template<typename T, typename ...Args>
		T& AddComponent(Args &&...args) 
		{
			return scene->registry.emplace<T>(entityId, std::forward<Args>(args)...);
		}
		template <typename T>
		void RemoveComponent()
		{
			scene->registry.remove<T>(entityId);
		}

		template <typename T>
		bool HasComponent() const
		{
			return scene->registry.all_of<T>(entityId);
		}

		template<typename T>
		T& GetComponent()
		{
			return scene->registry.get<T>(entityId);
		}

		operator bool() const
		{
			return entityId != entt::null;
		}

		operator entt::entity() const
		{
			return entityId;
		}

		bool operator==(Entity& other) const
		{
			return other.entityId == entityId && other.scene == scene;
		}

		operator void* () const
		{
			return (void*)(uint64_t)(uint32_t)entityId;
		}

	private:
		entt::entity entityId = entt::null;
		GameScene* scene = nullptr;
	};
}