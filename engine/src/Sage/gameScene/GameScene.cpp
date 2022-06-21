#include "GameScene.h"

#include "Entity.h"
#include "Components.h"
#include "Sage/renderer/renderer.hpp"
#include "Sage/System/AnimatorSystem.h"
#include <glm/gtx/matrix_transform_2d.hpp>

namespace Sage {
	GameScene::GameScene()
	{
	}
	
	GameScene::GameScene(const std::string& sceneName):
		name(sceneName)
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
				auto [transformComponent, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
				std::shared_ptr<Texture> toBeRendered = nullptr;

				if (!sprite.texture)
				{
					toBeRendered = TextureManager::loadWhiteTexture();
				}
				else
				{
					toBeRendered = sprite.texture;
				}
				glm::mat3 transform = glm::translate(glm::mat3(1.0f), transformComponent.Position) * 
					glm::rotate(glm::mat3(1.0f), transformComponent.Rotation) * 
					glm::scale(glm::mat3(1.0f), transformComponent.Scale);
				Renderer::RenderRotatedTexture(toBeRendered.get(), { 0, 0, 1.0f, 1.0f }, transform, sprite.Color);
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