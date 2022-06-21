#include "InspectorPanel.h"
#include "imgui.h"
#include "Sage/gameScene/Components.h"
#include "Sage/Core/Log.h"
#include <filesystem>

namespace Sage {
	InspectorPanel::InspectorPanel(Entity selectedEntity):
		selected(selectedEntity)
	{
	}

	template<typename T, typename Function>
	static void DrawComponent(const char* componentName, bool deletable, Entity selectedEntity, Function function)
	{
		if (!selectedEntity.HasComponent<T>())
			return;

		bool open = ImGui::TreeNodeEx(componentName, ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_SpanAvailWidth);
		
		bool removed = false;
		if (deletable)
		{
			ImGui::OpenPopupOnItemClick("Options Popup");

			if (ImGui::BeginPopup("Options Popup"))
			{
				if (ImGui::Selectable("Delete Component"))
				{
					removed = true;
				}
				ImGui::EndPopup();
			}
		}

		if (open)
		{
			function(selectedEntity.GetComponent<T>());
			ImGui::TreePop();
		}

		if (removed)
		{
			selectedEntity.RemoveComponent<T>();
		}
	}

	void InspectorPanel::OnImGuiRender()
	{
		if (!selected)
			return;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, { 300, 300 });
		ImGui::Begin("Inspector");
		ImGui::PopStyleVar();
		if (selected.HasComponent<NameComponent>())
		{
			auto& name = selected.GetComponent<NameComponent>().Name;
			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			strcpy_s(buffer, sizeof(buffer), name.c_str());
			if (ImGui::InputText("Name", buffer, sizeof(buffer)))
			{
				name = buffer;
			}
		}
		ImGui::SameLine(ImGui::GetWindowWidth() - 50);
		if (ImGui::Button("Add +"))
		{
			ImGui::OpenPopup("Component Popup");
		}
		bool openError = false;
		if (ImGui::BeginPopup("Component Popup"))
		{
			if (ImGui::Selectable("Sprite Renderer Component"))
			{
				if (!selected.HasComponent<SpriteRendererComponent>())
				{
					selected.AddComponent<SpriteRendererComponent>();
				}
				else
				{
					openError = true;
				}
			}
			
			if (ImGui::Selectable("Animator Component"))
			{
				if (!selected.HasComponent<AnimatorComponent>())
				{
					selected.AddComponent<AnimatorComponent>();
					if (!selected.HasComponent<SpriteRendererComponent>())
					{
						selected.AddComponent<SpriteRendererComponent>();
					}
				}
				else
				{
					openError = true;
				}
			}

			ImGui::EndPopup();
		}

		if (openError)
			ImGui::OpenPopup("Can't add component");

		ImVec2 center = ImGui::GetMainViewport()->GetCenter();
		ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

		if (ImGui::BeginPopupModal("Can't add component", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::Text("This component already exists in the entity!");
			float windowCenter = ImGui::GetWindowSize().x / 2;
			ImGui::SetCursorPosX(windowCenter);
			if (ImGui::Button("OK"))
			{
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}

		ImGui::Separator();
		DrawComponent<TransformComponent>("Transform", false, selected, [](auto& component) {
			ImGui::DragFloat2("Position", (float*)&component.Position, 0.025);
			if (ImGui::IsItemClicked(1))
			{
				component.Position.x = 0;
				component.Position.y = 0;
			}
			ImGui::DragFloat2("Scale", (float*)&component.Scale, 0.005f, 0.0f, FLT_MAX, "%.2f", ImGuiSliderFlags_AlwaysClamp);
			if (ImGui::IsItemClicked(1))
			{
				component.Scale.x = 1.0;
				component.Scale.y = 1.0;
			}
			ImGui::DragFloat("Rotation", &component.Rotation);
			if (ImGui::IsItemClicked(1))
			{
				component.Rotation = 0.0f;
			}
		});

		ImGui::Separator();
		DrawComponent<SpriteRendererComponent>("Sprite Renderer", true, selected, [](auto& component) {
			if (ImGui::ColorEdit3("Color", &component.Color.r))
			{
				/*component.Color.r = color.r;
				component.Color.g = (int)(color.g * 255.0f);
				component.Color.b = (int)(color.b * 255.0f);*/
			}
			ImGui::Text("Texture:");
			if (ImGui::BeginDragDropTarget())
			{
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Texture_Path"))
				{
					const char* data = (const char*)payload->Data;
					component.texture = TextureManager::load(data);
					std::hash<std::string> hasher;
					component.hash = hasher(data);
				}
				ImGui::EndDragDropTarget();
			}

			if (component.texture)
			{
				ImGui::Image(component.texture->GetRendererID(), { 75, 75 });
			}
			else
			{
				ImGui::SameLine();
				ImGui::Text("None");
				if (ImGui::BeginCombo("Mode", "None"))
				{
					if (ImGui::Selectable("None"))
					{

					}

					if (ImGui::Selectable("Rectangle"))
					{

					}
					ImGui::EndCombo();
				}
			}
		});
		
		ImGui::Separator();
		DrawComponent<AnimatorComponent>("Animator", true, selected, [](auto& component) {
			ImGui::DragInt2("Sheet Grid", &component.SheetGrid.x, 0.25f, 1, 100, "%d", ImGuiSliderFlags_AlwaysClamp);
			ImGui::DragInt("Speed", &component.Speed, 0.25f, 0, 100, "%d", ImGuiSliderFlags_AlwaysClamp);
		});

		ImGui::End();
		//ImGui::ShowDemoWindow();
	}
}