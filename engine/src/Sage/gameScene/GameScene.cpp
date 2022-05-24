#include "GameScene.h"

#include "Entity.h"
#include "Components.h"
#include "Sage/renderer/renderer.hpp"

namespace Sage {
	GameScene::GameScene()
	{
		
	}

	Entity GameScene::CreateEntity()
	{
		Entity newEntity = { registry.create(), this };
		newEntity.AddComponent<TransformComponent>();
		newEntity.AddComponent<NameComponent>();
		return newEntity;
	}

	void GameScene::DestroyEntity(Entity entity)
	{
		registry.destroy(entity);
	}

	void GameScene::OnRender()
	{
		auto group = registry.group<SpriteRendererComponent>(entt::get<TransformComponent>);

		for (auto entity : group)
		{
			auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

			Renderer::RenderTexture(sprite.texture.get(), Point{ transform.position.x, transform.position.y },
				Point{(int)sprite.texture->getWidth(), (int)sprite.texture->getWidth()}, sprite.color);
		}
	}
}