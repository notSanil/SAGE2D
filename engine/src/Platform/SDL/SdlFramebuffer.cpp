#include "SdlFramebuffer.h"
#include <SDL.h>
#include "Platform/SDL/SdlRenderer.h"


namespace Sage {
	SdlFramebuffer::SdlFramebuffer(uint32_t width, uint32_t height):
		width(width), height(height)
	{
		texture = Texture::Create(width, height, AccessFormat::Target);
	}

	SdlFramebuffer::~SdlFramebuffer()
	{
	}

	void SdlFramebuffer::Resize(uint32_t width, uint32_t height)
	{
		this->width = width;
		this->height = height;

		texture = Texture::Create(width, height, AccessFormat::Target);
	}

	void SdlFramebuffer::Bind()
	{
		SDL_SetRenderTarget(SdlRenderer::GetSDLRenderer(), (SDL_Texture*)texture->GetRendererID());
	}

	void SdlFramebuffer::Unbind()
	{
		SDL_SetRenderTarget(SdlRenderer::GetSDLRenderer(), nullptr);
	}
}