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


		bool deleted = false;
		if (ImGui::IsWindowFocused())
		{
			if (ImGui::IsKeyPressed(ImGuiKey_Delete))
			{
				deleted = true;
			}
		}

		if (ImGui::BeginPopupContextWindow(NULL, ImGuiPopupFlags_NoOpenOverItems | ImGuiPopupFlags_MouseButtonRight))
		{
			if (ImGui::MenuItem("Create Empty Entity"))
				sceneContext->CreateEntity();

			ImGui::EndPopup();
		}

		/*if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered(ImGuiHoveredFlags_None))
			SetSelectedEntity({});*/
		ImGui::End();
		inspector.OnImGuiRender();

		if (deleted && currentlySelected)
		{
			sceneContext->DestroyEntity(currentlySelected);
			SetSelectedEntity({});
		}
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
			bool open = ImGui::TreeNodeEx((void*)entity, flags, name.c_str());

			bool deleted = false;
			if (ImGui::BeginPopupContextItem())
			{
				if (ImGui::Selectable("Delete"))
				{
					deleted = true;
				}
				ImGui::EndPopup();
			}

			if (ImGui::IsItemClicked())
			{
				SetSelectedEntity(entity);
			}
			if (open)
			{
				ImGui::TreePop();
			}

			if (deleted)
			{
				if (entity == currentlySelected)
				{
					SetSelectedEntity({});
				}
				sceneContext->DestroyEntity(entity);				
			}
		}
	}
}
