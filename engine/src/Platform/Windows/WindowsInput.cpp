#include "Sage/Core/Input.h"
#include <SDL_keycode.h>
#include <SDL_keyboard.h>
#include <SDL_mouse.h>


namespace Sage {
	glm::vec2 Input::GetMousePos()
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		return { (float)x, (float)y };
	}

	float Input::GetMouseX()
	{
		return GetMousePos().x;
	}

	float Input::GetMouseY()
	{
		return GetMousePos().y;
	}
}