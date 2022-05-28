#include "InspectorPanel.h"
#include "imgui.h"
#include "Sage/gameScene/Components.h"
#include "Sage/Core/Log.h"

namespace Sage {
	InspectorPanel::InspectorPanel(Entity selectedEntity):
		selected(selectedEntity)
	{
	}

	template<typename T, typename Function>
	static void DrawComponent(const char* componentName, Entity selectedEntity, Function function)
	{
		if (!selectedEntity.HasComponent<T>())
			return;

		if (ImGui::TreeNodeEx(componentName, ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_SpanAvailWidth))
		{
			function(selectedEntity.GetComponent<T>());
			ImGui::TreePop();
		}
	}

	void InspectorPanel::OnImGuiRender()
	{
		if (!selected)
			return;

		ImGui::Begin("Inspector");

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

		ImGui::Separator();
		DrawComponent<TransformComponent>("Transform", selected, [](auto& component) {
			ImGui::DragInt2("Position", (int*)&component.Position);
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
		DrawComponent<SpriteRendererComponent>("Sprite Renderer", selected, [](auto& component) {
			Vec4<float> color{ (float)component.Color.r / 255.0f, (float)component.Color.g / 255.0f,
				(float)component.Color.b / 255.0f, 1.0f };
			if (ImGui::ColorEdit3("Color", (float*)color))
			{
				component.Color.r = (int)(color.r * 255.0f);
				component.Color.g = (int)(color.g * 255.0f);
				component.Color.b = (int)(color.b * 255.0f);
			}
		});


		ImGui::End();
		//ImGui::ShowDemoWindow();
	}
	
}