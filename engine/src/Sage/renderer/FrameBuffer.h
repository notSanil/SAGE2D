#pragma once
#include <memory>


namespace Sage {
	class Framebuffer
	{
	public:
		virtual ~Framebuffer() = default;

		virtual uint32_t GetWidth() = 0;
		virtual uint32_t GetHeight() = 0;

		virtual void Resize(uint32_t width, uint32_t height) = 0;

		virtual void* GetTextureId() = 0;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		static std::unique_ptr<Framebuffer> Create(int width, int height);
	};
}