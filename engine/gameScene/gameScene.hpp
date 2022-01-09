#pragma once

#include <SDL2/SDL.h>
#include <vector>

#include "../gameObject/gameObject.hpp"


class GameScene{
protected:
    std::vector <GameObject*> objects;

    int dispHeight, dispWidth;

    SDL_Renderer *renderer;

public:
    GameScene(){};
    virtual ~GameScene(){};
    virtual void on_render() = 0;
    virtual void on_step() = 0;
    virtual void on_event(SDL_Event &e) = 0;
    virtual void on_exit() = 0;
};