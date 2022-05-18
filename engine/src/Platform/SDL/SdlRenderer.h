#pragma once
#include <SDL.h>
#include "Platform/Windows/WindowsWindow.h"
#include "Sage/renderer/font.hpp"
#include "Platform/SDL/SdlTexture.h"
#include "Sage/transform/Vec4.h"

namespace Sage {
	class SdlRenderer
	{
    public:
        static void init(const WindowsWindow* window);
        static void destroy();

        static SDL_Renderer* GetSDLRenderer();

        static void StartScene();
        static void EndScene();

        static void RenderText(const Font* font, std::string const& text, Vec4 const& col, Point const pos);
        static void RenderTexture(SdlTexture* texture, Point pos, Point dims);
        static void RenderTexture(SdlTexture* texture, Vec4 texSize, Vec4 destSize);
        static void RenderRect(Point pos, Point dims, int r, int g, int b);
	private:
		static SDL_Renderer* renderer;
	};
}