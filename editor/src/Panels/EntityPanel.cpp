#include "EntityPanel.h"
#include <imgui.h>
#include "Sage/gameScene/Components.h"


namespace Sage {
	EntityPanel::EntityPanel(GameScene* currentActiveScene)
		:sceneContext(currentActiveScene)
	{
	}
	
	void EntityPanel::OnImGuiRender()
	{
		ImGui::Begin("Scene");
		sceneContext->registry.each([&](entt::entity entity) {
			Entity e{ entity, sceneContext };
			DrawEntityNode(e);
		});

		/*if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered(ImGuiHoveredFlags_None))
			SetSelectedEntity({});*/
		ImGui::End();
		//ImGui::ShowDemoWindow();
		inspector.OnImGuiRender();
	}

	void EntityPanel::SetSelectedEntity(Entity e)
	{
		currentlySelected = e;
		inspector.SetSelectedEntity(e);		
	}

	void EntityPanel::DrawEntityNode(Entity entity)
	{
		if (entity.HasComponent<NameComponent>())
		{
			const std::string& name = entity.GetComponent<NameComponent>().Name;
			
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow;
			if (currentlySelected == entity)
				flags |= ImGuiTreeNodeFlags_Selected;
			if (ImGui::TreeNodeEx((void*)entity, flags, name.c_str()))
			{
				ImGui::TreePop();
			}

			if (ImGui::IsItemClicked())
			{
				SetSelectedEntity(entity);
			}
			
		}
	}
}
