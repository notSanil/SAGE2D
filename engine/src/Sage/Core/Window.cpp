#include "Window.h"
#include <Platform/Windows/WindowsWindow.h>

namespace Sage {
	std::unique_ptr<Window> Window::Create(WindowProperties& properties)
	{
		return std::make_unique<WindowsWindow>(properties);
	}
	Window::~Window()
	{
	}
}