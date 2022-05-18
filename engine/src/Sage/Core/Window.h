#pragma once
#include <cinttypes>
#include <memory>
#include <string>

namespace Sage {
	struct WindowProperties
	{
		uint32_t width = 0, height = 0;
		std::string name;
	};

	class Window
	{
	public:
		static std::unique_ptr<Window> Create(WindowProperties& properties);
		virtual ~Window() = 0;

		virtual uint32_t GetWidth() = 0;
		virtual uint32_t GetHeight() = 0;
		virtual std::string GetName() = 0;
	};
}