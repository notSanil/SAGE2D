#pragma once

#include <SDL2/SDL.h>
#include "../exceptions/sdlException.hpp"

class Renderer{
private:
    static SDL_Renderer* renderer;
    Renderer(){};

public:
    static void init(SDL_Window *window){
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (!renderer){
            throw SDLException(Renderer_Failed);
        }
    }

    static SDL_Renderer* get(){
        return renderer;
    }

    static void destroy(){
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
};

SDL_Renderer* Renderer::renderer = nullptr;