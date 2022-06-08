#include "SdlRenderer.h"
#include "Sage/Core/Log.h"
#include "Sage/renderer/text_renderer.hpp"

namespace Sage{
	SDL_Renderer* SdlRenderer::renderer = nullptr;


	void SdlRenderer::init(const WindowsWindow* window)
	{
		if (renderer != nullptr)
		{
			SAGE_CORE_WARN("Renderer alredy created");
			return;
		}
		renderer = SDL_CreateRenderer(window->windowData.windowContext, -1, SDL_RENDERER_ACCELERATED);
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	}

	void SdlRenderer::destroy()
	{
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}

	SDL_Renderer* SdlRenderer::GetSDLRenderer()
	{
		return renderer;
	}

	void SdlRenderer::StartScene()
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
	}

	void SdlRenderer::EndScene()
	{
		SDL_RenderPresent(renderer);
	}

	/*void SdlRenderer::RenderText(const Font* font, std::string const& text, Vec4 const& col, glm::ivec2 const pos)
	{
		TextRenderer::get()->renderText(font, text, col, pos);
	}*/

	void SdlRenderer::RenderTexture(SdlTexture* texture, glm::ivec2 pos, glm::ivec2 dims, glm::ivec4 color)
	{
		Uint8 r, g, b;
		SDL_GetTextureColorMod(texture->texture, &r, &g, &b);
		SDL_Rect destSize{ pos.x, pos.y, dims.x, dims.y };
		SDL_SetTextureColorMod(texture->texture, color.r, color.g, color.b);
		SDL_RenderCopy(renderer, texture->texture, NULL, &destSize);
		SDL_SetTextureColorMod(texture->texture, r, g, b);
	}

	void SdlRenderer::RenderTexture(SdlTexture* texture, glm::ivec4 texSize, glm::ivec4 destSize, glm::ivec4 color)
	{
		Uint8 r, g, b;
		SDL_GetTextureColorMod(texture->texture, &r, &g, &b);
		SDL_SetTextureColorMod(texture->texture, color.r, color.g, color.b);
		SDL_RenderCopy(renderer, texture->texture, (SDL_Rect*)&texSize, (SDL_Rect*)&destSize);
		SDL_SetTextureColorMod(texture->texture, r, g, b);
	}

	void SdlRenderer::RenderTexture(SdlTexture* texture, glm::ivec4 texSize, glm::imat3x2& transform, glm::ivec4 color)
	{
		SDL_Rect dest_rect = { transform[0][0], transform[0][1], 
			(float)texSize.z * transform[1][0], 
			(float)texSize.w * transform[1][1] };
		Uint8 r, g, b;
		SDL_GetTextureColorMod(texture->texture, &r, &g, &b);
		SDL_SetTextureColorMod(texture->texture, color.r, color.g, color.b);
		SDL_RenderCopy(renderer, texture->texture, (SDL_Rect*)&texSize, &dest_rect);
		SDL_SetTextureColorMod(texture->texture, r, g, b);
	}

	void SdlRenderer::RenderRotatedTexture(SdlTexture* texture, glm::ivec4 texSize, glm::imat3x2& transform, glm::ivec4 color)
	{
		SDL_Rect dest_rect = { transform[0][0], transform[0][1],
			(float)texSize.z * transform[1][0],
			(float)texSize.w * transform[1][1] };
		Uint8 r, g, b;
		SDL_GetTextureColorMod(texture->texture, &r, &g, &b);
		SDL_SetTextureColorMod(texture->texture, color.r, color.g, color.b);
		SDL_RenderCopyEx(renderer, texture->texture, (SDL_Rect*)&texSize, &dest_rect, transform[2][0], NULL, SDL_FLIP_NONE);
		SDL_SetTextureColorMod(texture->texture, r, g, b);
	}

	void SdlRenderer::RenderRect(glm::ivec2 pos, glm::ivec2 dims, int r, int g, int b)
	{
		SDL_SetRenderDrawColor(renderer, r, g, b, 255);
		SDL_Rect dest{ pos.x, pos.y, dims.x, dims.y };
		SDL_RenderDrawRect(renderer, &dest);
	}
}