#pragma once
#include "Sage/texture/texture.hpp"
#include <string>
#include <SDL.h>


namespace Sage {
	class SdlTexture : public Texture
	{
	public:
		SdlTexture(uint32_t width, uint32_t height);
		SdlTexture(uint32_t width, uint32_t height, AccessFormat format);
		SdlTexture(const std::string& path);
		virtual ~SdlTexture() override;

		virtual void Bind() override {};
		virtual void Unbind() override {};
		virtual uint32_t getWidth() override { return width; };
		virtual uint32_t getHeight() override { return height; };

		virtual void setData(void* data) override;
		
		virtual void* GetRendererID() override { return (void*)texture; };

	private:
		SDL_Texture* texture;
		uint32_t width, height;
		friend class SdlRenderer;
	};
}