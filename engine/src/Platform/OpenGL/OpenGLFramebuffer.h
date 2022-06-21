#pragma once
#include "Sage/renderer/FrameBuffer.h"
#include "Sage/texture/Texture.hpp"

namespace Sage {
	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(int width, int height);
		virtual ~OpenGLFramebuffer();

		virtual uint32_t GetWidth() override { return width; };
		virtual uint32_t GetHeight() override { return height; };

		virtual void Resize(uint32_t width, uint32_t height) override;

		virtual void* GetTextureId() override { return (void*)(uint64_t)colorAttachmentId; };

		virtual void Bind() override;
		virtual void Unbind() override;
	private:
		uint32_t id;
		uint32_t colorAttachmentId;
		uint32_t depthStencilId;
		uint32_t width, height;
	};
}