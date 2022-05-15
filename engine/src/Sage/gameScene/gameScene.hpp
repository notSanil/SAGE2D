#pragma once

#include <SDL.h>


class GameScene{
public:
    GameScene(){};
    virtual ~GameScene(){};
    virtual void on_render() = 0;
    virtual void on_step(const float dt) = 0;
    virtual void on_event(const SDL_Event &e) = 0;
};