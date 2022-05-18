#include "WindowsWindow.h"
#include "Sage/Core/Log.h"

namespace Sage{
	WindowsWindow::WindowsWindow(WindowProperties& properties)
	{
		windowData.properties = properties;
		SDL_Window* window = SDL_CreateWindow(properties.name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
			properties.width, properties.height, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			SAGE_CORE_CRIT("Window creation failed!");
		}
		windowData.windowContext = window;
	}

	WindowsWindow::~WindowsWindow()
	{
		SDL_DestroyWindow(windowData.windowContext);
		windowData.windowContext = nullptr;
	}

	uint32_t WindowsWindow::GetWidth()
	{
		return windowData.properties.width;
	}

	uint32_t WindowsWindow::GetHeight()
	{
		return windowData.properties.height;
	}

	std::string WindowsWindow::GetName()
	{
		return windowData.properties.name;
	}
}