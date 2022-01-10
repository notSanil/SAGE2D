#include "renderer.hpp"


Renderer::Renderer(){};

void Renderer::init(SDL_Window *window){
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer){
        throw SDLException(Renderer_Failed);
    }
}

SDL_Renderer* Renderer::get(){
    return renderer;
}

void Renderer::destroy(){
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
}
SDL_Renderer* Renderer::renderer = nullptr;
