#pragma once
#include "Sage/Core/Keycodes.h"
#include "Sage/Core/MouseCodes.h"
#include "Sage/Events/KeyEvent.h"
#include "Sage/Events/MouseEvent.h"
#include <glm/glm.hpp>
#include <unordered_map>

namespace Sage {
	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode code);
		static bool IsMouseButtonPressed(MouseCode code);

		static glm::vec2 GetMousePos();
		static float GetMouseX();
		static float GetMouseY();

		static void OnKeyPressed(KeyPressedEvent& e);
		static void OnKeyReleased(KeyPressedEvent& e);

		static void OnMouseButtonPressed(MouseButtonPressedEvent& e);
		static void OnMouseButtonReleased(MouseButtonReleasedEvent& e);
	private:
		static std::unordered_map<KeyCode, bool> isPressed;
		static std::unordered_map<MouseCode, bool> isMousePressed;
	};
}