#include "BrowserPanel.h"
#include "imgui.h"
#include <filesystem>
#include "Sage/Core/Log.h"
namespace Sage {
	static std::filesystem::path root = "assets";
	BrowserPanel::BrowserPanel()
		:currentPath(root)
	{
		folderIcon = Texture::Create("resources/folder-solid.png");
		fileIcon = Texture::Create("resources/file-solid.png");
	}

	void BrowserPanel::OnImGuiRender()
	{
		ImGui::Begin("Browser");

		if (currentPath != root)
		{
			if (ImGui::Button("<"))
			{
				currentPath = currentPath.parent_path();
			}
		}

		static float padding = 16.0f;
		static float thumbnailSize = 64;
		float cellSize = thumbnailSize + padding;

		float panelWidth = ImGui::GetContentRegionAvail().x;
		int columnCount = (int)(panelWidth / cellSize);
		if (columnCount < 1)
			columnCount = 1;

		ImGui::Columns(columnCount, 0, false);

		ImGui::PushStyleColor(ImGuiCol_Button, { 0, 0, 0, 0 });
		for (auto const& dir_entry : std::filesystem::directory_iterator(currentPath))
		{
			auto& name = dir_entry.path().filename();
			if (std::filesystem::is_directory(dir_entry.path()))
			{
				ImGui::PushID(dir_entry.path().string().c_str());
				if (ImGui::ImageButton(folderIcon->GetRendererID(), { thumbnailSize, thumbnailSize }, { 0, 0 }, { 1, 1 }, -1, { 0, 0, 0, 0 }, {0.1, 0.3, 0.6, 1}))
				{
					currentPath /= name;
				}
				ImGui::TextWrapped(name.string().c_str());
				ImGui::NextColumn();
				ImGui::PopID();
			}
			else
			{
				ImGui::PushID(dir_entry.path().string().c_str());
				ImGui::ImageButton(fileIcon->GetRendererID(), {thumbnailSize, thumbnailSize});

				if (name.extension().string() == ".png")
				{
					if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
					{
						ImGui::SetDragDropPayload("Texture_Path", dir_entry.path().string().c_str(), dir_entry.path().string().size() + 1);
						ImGui::Text(name.string().c_str());
						ImGui::EndDragDropSource();
					}
				}
				ImGui::TextWrapped(name.string().c_str());
				ImGui::NextColumn();
				ImGui::PopID();
			}
		}
		ImGui::PopStyleColor();
		ImGui::Columns(1);
		ImGui::End();

		//ImGui::ShowDemoWindow();
	}
}