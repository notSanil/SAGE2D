#pragma once
#include "Sage/renderer/FrameBuffer.h"
#include "Sage/texture/Texture.hpp"

namespace Sage {
	class SdlFramebuffer : public Framebuffer
	{
	public:
		SdlFramebuffer(uint32_t width, uint32_t height);
		virtual ~SdlFramebuffer() override;

		virtual uint32_t GetWidth() override { return width; };
		virtual uint32_t GetHeight() override { return height; };

		virtual void Resize(uint32_t width, uint32_t height) override;

		virtual void* GetTextureId() override { return texture->GetRendererID(); };

		virtual void Bind() override;
		virtual void Unbind() override;

	private:
		std::unique_ptr<Texture> texture;
		uint32_t width, height;
	};
}