#pragma once
#include <filesystem>
#include <Sage/Sage.h>
#include <memory>

namespace Sage {
	class BrowserPanel
	{
	public:
		BrowserPanel();
		void OnImGuiRender();

	private:
		std::filesystem::path currentPath;

		std::unique_ptr<Texture> folderIcon;
		std::unique_ptr<Texture> fileIcon;
	};
}