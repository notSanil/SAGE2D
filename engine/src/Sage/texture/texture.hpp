#pragma once
#include <string>
#include <unordered_map>

#include <SDL.h>
#include <SDL_image.h>



class Texture{
public:
    static SDL_Texture* loadTexture(std::string const &path);
    static void destroyAllTextures();
    static void destroyTexture(std::string const &path);

private:
    static std::unordered_map<std::string, SDL_Texture*> loadedTextures;
    Texture();
};