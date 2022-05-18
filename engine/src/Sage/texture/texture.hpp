#pragma once
#include <string>
#include <unordered_map>
#include <memory>

namespace Sage {
    class Texture
    {
    public:
        static std::unique_ptr<Texture> Create(uint32_t width, uint32_t height);
        static std::unique_ptr<Texture> Create(const std::string& path);
        virtual ~Texture() = 0 {};

        virtual uint32_t getWidth() = 0;
        virtual uint32_t getHeight() = 0;
        virtual void setData(void* data) = 0;
    };

    class TextureManager
    {
    public:
        static std::shared_ptr<Texture> load(const std::string& path);

    private:
        static std::unordered_map<std::string, std::shared_ptr<Texture>> loadedTextures;
    };

}