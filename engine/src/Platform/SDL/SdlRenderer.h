#pragma once
#include <SDL.h>
#include "Platform/Windows/WindowsWindow.h"
//#include "Sage/renderer/font.hpp"
#include "Platform/SDL/SdlTexture.h"
#include <glm/glm.hpp>


namespace Sage {
	class SdlRenderer
	{
    public:
        static void init(const WindowsWindow* window);
        static void destroy();

        static SDL_Renderer* GetSDLRenderer();

        static void StartScene();
        static void EndScene();

        //static void RenderText(const Font* font, std::string const& text, Vec4 const& col, glm::ivec2 const pos);
        static void RenderTexture(SdlTexture* texture, glm::ivec2 pos, glm::ivec2 dims, glm::ivec4 color = { 255, 255, 255, 255 });
        static void RenderTexture(SdlTexture* texture, glm::ivec4 texSize, glm::ivec4 destSize, glm::ivec4 color = { 255, 255, 255, 255 });
        static void RenderTexture(SdlTexture* texture, glm::ivec4 texSize, glm::imat3x2& transform, glm::ivec4 color = { 255, 255, 255, 255 });
        static void RenderRotatedTexture(SdlTexture* texture, glm::ivec4 texSize, glm::imat3x2& transform, glm::ivec4 color = { 255, 255, 255, 255 });
        static void RenderRect(glm::ivec2 pos, glm::ivec2 dims, int r, int g, int b);
	private:
		static SDL_Renderer* renderer;
	};
}