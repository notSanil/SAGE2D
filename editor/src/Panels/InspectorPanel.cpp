#include "InspectorPanel.h"
#include "imgui.h"
#include "Sage/gameScene/Components.h"
#include "Sage/Core/Log.h"

namespace Sage {
	InspectorPanel::InspectorPanel(Entity selectedEntity):
		selected(selectedEntity)
	{
	}

	void InspectorPanel::OnImGuiRender()
	{
		if (!selected)
			return;

		ImGui::Begin("Inspector");

		if (selected.HasComponent<NameComponent>())
		{
			auto& name = selected.GetComponent<NameComponent>().name;
			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			strcpy_s(buffer, sizeof(buffer), name.c_str());
			if (ImGui::InputText("Name", buffer, sizeof(buffer)))
			{
				name = buffer;
			}
		}
		ImGui::Separator();

		if (selected.HasComponent<TransformComponent>())
		{
			auto& transform = selected.GetComponent<TransformComponent>();
			ImGui::DragInt2("Position", (int*)&transform.position);
			if (ImGui::IsItemClicked(1))
			{
				transform.position.x = 0;
				transform.position.y = 0;
			}
			ImGui::DragFloat2("Scale", (float*)&transform.Scale, 0.05f, 0.0f, FLT_MAX, "%.2f", ImGuiSliderFlags_AlwaysClamp);
		}

		ImGui::End();
		//ImGui::ShowDemoWindow();
	}
}