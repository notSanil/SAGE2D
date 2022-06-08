#include "GameScene.h"

#include "Entity.h"
#include "Components.h"
#include "Sage/renderer/renderer.hpp"
#include "Sage/System/AnimatorSystem.h"

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

	Entity GameScene::CreateEntity(uint32_t id)
	{
		Entity newEntity = { registry.create((entt::entity)id), this };
		return newEntity;
	}

	void GameScene::DestroyEntity(Entity entity)
	{
		registry.destroy(entity);
	}

	void GameScene::OnRender()
	{
		{
			auto group = registry.group<SpriteRendererComponent>(entt::get<TransformComponent>, entt::exclude<AnimatorComponent>);

			for (auto entity : group)
			{
				auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
				std::shared_ptr<Texture> toBeRendered = nullptr;
				int width = 1;
				int height = 1;

				if (!sprite.texture)
				{
					toBeRendered = TextureManager::loadWhiteTexture();
				}
				else
				{
					toBeRendered = sprite.texture;
					width = (int)sprite.texture->getWidth();
					height = (int)sprite.texture->getHeight();
				}
				Renderer::RenderRotatedTexture(toBeRendered.get(), { 0, 0, width, height }, (glm::imat3x2)transform, sprite.Color);
			}
		}

		{
			auto animatedGroup = registry.group<AnimatorComponent>(entt::get<TransformComponent, SpriteRendererComponent>);

			for (auto entity : animatedGroup)
			{
				auto [transform, sprite, animation] = animatedGroup.get<TransformComponent, SpriteRendererComponent, AnimatorComponent>(entity);
				AnimatorSystem::RenderFrame(animation, sprite, transform);
				AnimatorSystem::MoveToNextFrame(animation, animation.Speed);
			}
		}
	}
}