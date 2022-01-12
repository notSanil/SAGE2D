#include "texture.hpp"


std::unordered_map<std::string, SDL_Texture*> Texture::loadedTextures;

SDL_Texture* Texture::loadTexture(std::string const &path){
    auto location = loadedTextures.find(path);
    if (location != loadedTextures.end()){
        return location -> second;
    }

    SDL_Texture* texture = IMG_LoadTexture(Renderer::get(), path.c_str());
    if (texture == NULL){
        //return an exception
    }
    loadedTextures[path] = texture;
    return texture;
}

void Texture::destroyAllTextures(){
    for (auto &object: loadedTextures){
        SDL_DestroyTexture(object.second);
    }

    loadedTextures.clear();
}

void Texture::destroyTexture(std::string const &path){
    auto location = loadedTextures.find(path);
    if (location != loadedTextures.end()){
        SDL_DestroyTexture(location -> second);
    }
    loadedTextures.erase(location);
}

Texture::Texture(){};
