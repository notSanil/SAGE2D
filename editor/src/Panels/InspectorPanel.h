#pragma once

#include "Sage/gameScene/Entity.h"
namespace Sage {
	class InspectorPanel
	{
	public:
		InspectorPanel() = default;
		InspectorPanel(Entity selectedEntity);
		~InspectorPanel() = default;

		void SetSelectedEntity(Entity entity) { selected = entity; }

		void OnImGuiRender();
	private:
		Entity selected;

	};
}