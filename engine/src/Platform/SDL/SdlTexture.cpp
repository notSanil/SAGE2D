#include "SdlTexture.h"
#include "Sage/renderer/renderer.hpp"
#include "Sage/Core/Log.h"
#include "Platform/SDL/SdlRenderer.h"
#include <SDL_image.h>

namespace Sage {

	SdlTexture::SdlTexture(uint32_t width, uint32_t height) : 
		width(width), height(height)
	{
		texture = SDL_CreateTexture(SdlRenderer::GetSDLRenderer(), 
			SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, width, height);
	}

	SdlTexture::SdlTexture(uint32_t width, uint32_t height, AccessFormat format):
		width(width), height(height)
	{
		SDL_TextureAccess access = SDL_TEXTUREACCESS_STATIC;
		switch (format)
		{
		case AccessFormat::Static:
			access = SDL_TEXTUREACCESS_STATIC;
			break;
		case AccessFormat::Streaming:
			access = SDL_TEXTUREACCESS_STREAMING;
			break;
		case AccessFormat::Target:
			access = SDL_TEXTUREACCESS_TARGET;
			break;
		default:
			SAGE_CORE_ERROR("Unknown texture format.");
			break;
		}

		texture = SDL_CreateTexture(SdlRenderer::GetSDLRenderer(),
			SDL_PIXELFORMAT_RGBA8888, access, width, height);
	}

	SdlTexture::SdlTexture(const std::string& path)
	{
		texture = IMG_LoadTexture(SdlRenderer::GetSDLRenderer(), path.c_str());
		if (texture == nullptr)
		{
			SAGE_CORE_ERROR("Failed to load texture. {0}", path);
		}
		int w, h;
		SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
		width = (uint32_t)w;
		height = (uint32_t)h;
	}

	SdlTexture::~SdlTexture()
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
		width = 0;
		height = 0;
	}

	void SdlTexture::setData(void* data)
	{
		//Pitch here is hardcoded to width * 4 bytes which might be incorrect for other formats
		int failed = SDL_UpdateTexture(texture, nullptr, data, width * 4);
		if (failed)
			SAGE_CORE_ERROR("Failed to assign data to texture");
	}

	void SdlTexture::setData(void* data, Vec4<int> dimensions)
	{
		//Pitch here is hardcoded to width * 4 bytes which might be incorrect for other formats
		int failed = SDL_UpdateTexture(texture, (SDL_Rect*)&dimensions, data, width * 4);
		if (failed)
			SAGE_CORE_ERROR("Failed to assign data to texture");
	}
}
