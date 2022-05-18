#include "texture.hpp"
#include "Sage/renderer/renderer.hpp"
#include "Sage/Core/Log.h"
#include "Platform/SDL/SdlTexture.h"

namespace Sage {
    std::unique_ptr<Texture> Texture::Create(uint32_t width, uint32_t height)
    {
        return std::make_unique<SdlTexture>(width, height);
    }

    std::unique_ptr<Texture> Texture::Create(const std::string& path)
    {
        return std::make_unique<SdlTexture>(path);
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

    std::unordered_map<std::string, std::shared_ptr<Texture>> TextureManager::loadedTextures;
}