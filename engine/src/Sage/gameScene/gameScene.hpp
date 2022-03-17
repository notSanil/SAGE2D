#pragma once

#include <SDL2/SDL.h>
#include <vector>

#include "Sage/gameObject/gameObject.hpp"


class GameScene{
protected:
    std::vector <GameObject*> objects;

    int dispHeight, dispWidth;

    SDL_Renderer *renderer;

public:
    GameScene(){};
    virtual ~GameScene(){};
    virtual void on_render() = 0;
    virtual void on_step(const float dt) = 0;
    virtual void on_event(const SDL_Event &e) = 0;
};