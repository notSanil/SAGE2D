#pragma once
#include "Sage/texture/Texture.hpp"

namespace Sage {
	class OpenGLTexture : public Texture
	{
    public:
        OpenGLTexture(uint32_t width, uint32_t height);
        OpenGLTexture(uint32_t width, uint32_t height, AccessFormat format);
        OpenGLTexture(const std::string& path);
        OpenGLTexture(const std::string& path, ResizingPolicy resizingPolicy);
        virtual ~OpenGLTexture() override;

        virtual void Bind() override;
        virtual void Unbind() override;
        virtual uint32_t getWidth() override { return width; };
        virtual uint32_t getHeight() override { return height; };
        virtual void setData(void* data) override;
        virtual void* GetRendererID() override { return (void*)(uint64_t)id; };
    private:
        uint32_t id;
        uint32_t width, height;
	};
}