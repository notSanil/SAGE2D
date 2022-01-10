#pragma once

#include <SDL2/SDL.h>
#include "../exceptions/sdlException.hpp"

class Renderer{
private:
    static SDL_Renderer* renderer;
    Renderer();

public:
    static void init(SDL_Window *window);
    static SDL_Renderer* get();
    static void destroy();
};

