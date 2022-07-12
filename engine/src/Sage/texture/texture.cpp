#include "texture.hpp"
#include "Sage/renderer/renderer.hpp"
#include "Sage/Core/Log.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Sage {
    std::unique_ptr<Texture> Texture::Create(uint32_t width, uint32_t height)
    {
        switch (RenderAPI::GetApi())
        {
        case API::OpenGL:
            return std::make_unique<OpenGLTexture>(width, height);
        default:
            return nullptr;
        }
    }

    std::unique_ptr<Texture> Texture::Create(uint32_t width, uint32_t height, AccessFormat format)
    {
        switch (RenderAPI::GetApi())
        {
        case API::OpenGL:
            return std::make_unique<OpenGLTexture>(width, height, format);
        default:
            return nullptr;
        }
    }

    std::unique_ptr<Texture> Texture::Create(const std::string& path)
    {
        switch (RenderAPI::GetApi())
        {
        case API::OpenGL:
            return std::make_unique<OpenGLTexture>(path);
        default:
            return nullptr;
        }
    }
    
    std::unique_ptr<Texture> Texture::Create(const std::string& path, ResizingPolicy resizingPolicy)
    {
        switch (RenderAPI::GetApi())
        {
        case API::OpenGL:
            return std::make_unique<OpenGLTexture>(path, resizingPolicy);
        default:
            return nullptr;
        }
    }


    //////////////////////Texture Manager////////////////////////////////
    std::shared_ptr<Texture> TextureManager::load(const std::string& path)
    {
        auto it = loadedTextures.find(path);
        if (it == loadedTextures.end())
        {
            std::shared_ptr newTex = Texture::Create(path);
            loadedTextures[path] = newTex;
            return newTex;
        }
        else
        {
            return it->second;
        }
    }

    std::shared_ptr<Texture> TextureManager::loadWhiteTexture()
    {
        if (whiteTexture)
            return whiteTexture;
        
        uint32_t data = 0xffffffff;
        whiteTexture = Texture::Create(1, 1);
        whiteTexture->setData(&data);
        return whiteTexture;
    }

    std::unordered_map<std::string, std::shared_ptr<Texture>> TextureManager::loadedTextures;
    std::shared_ptr<Texture> TextureManager::whiteTexture = nullptr;
}