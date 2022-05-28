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
			Transform t{ {transform.Position.x, transform.Position.y}, {transform.Scale.x, transform.Scale.y}, transform.Rotation };
			Renderer::RenderRotatedTexture(sprite.texture.get(), {0, 0, (int)sprite.texture->getWidth(), (int)sprite.texture->getHeight()}, t, sprite.Color);
		}
	}
}