#pragma once
#include <string>
#include <unordered_map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../renderer/renderer.hpp"


class Texture{
public:
    static SDL_Texture* loadTexture(std::string const &path);
    static void destroyAllTextures();
    static void destroyTexture(std::string const &path);

private:
    static std::unordered_map<std::string, SDL_Texture*> loadedTextures;
    Texture();
};