#include "Sage/Core/Input.h"

namespace Sage {
	std::unordered_map<KeyCode, bool> Input::isPressed;
	std::unordered_map<MouseCode, bool> Input::isMousePressed;
	bool Input::IsKeyPressed(KeyCode code)
	{
		if (isPressed.count(code) == 0)
			isPressed[code] = false;

		return isPressed[code];
	}

	bool Input::IsMouseButtonPressed(MouseCode code)
	{
		if (isMousePressed[code] == 0)
			isMousePressed[code] = false;

		return isMousePressed[code];
	}

	void Input::OnKeyPressed(KeyPressedEvent& e)
	{
		isPressed[e.GetKeyCode()] = true;
	}
	void Input::OnKeyReleased(KeyPressedEvent& e)
	{
		isPressed[e.GetKeyCode()] = false;
	}

	void Input::OnMouseButtonPressed(MouseButtonPressedEvent& e)
	{
		isMousePressed[e.GetMouseButton()] = true;
	}
	void Input::OnMouseButtonReleased(MouseButtonReleasedEvent& e)
	{
		isMousePressed[e.GetMouseButton()] = false;
	}
}