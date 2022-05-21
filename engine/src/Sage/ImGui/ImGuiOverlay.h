#pragma once
#include <imgui.h>

namespace Sage {
	class ImGuiOverlay
	{
	public:
		ImGuiOverlay();
		~ImGuiOverlay();

		void Begin();
		void End();
	private:
		const ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	};
}