#pragma once
#include "Sage/gameScene/GameScene.h"
#include "Sage/gameScene/Entity.h"
#include "InspectorPanel.h"

namespace Sage {
	class EntityPanel
	{
	public:
		EntityPanel() = default;
		EntityPanel(GameScene* currentActiveScene);
		~EntityPanel() = default;
		void OnImGuiRender();

		void SetSelectedEntity(Entity e);
		Entity GetSelectedEntity() const { return currentlySelected; }
		bool IsEntitySelected() const { return (bool)currentlySelected; }

		void SetSceneContext(GameScene* currentScene);
	private:
		void DrawEntityNode(Entity entity);

	private:
		GameScene* sceneContext = nullptr;
		Entity currentlySelected;

		InspectorPanel inspector;
	};
}