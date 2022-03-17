#pragma once
#include <SDL2/SDL.h>
#include "Sage/transform/point.hpp"


class GameObject{
protected:
    Point pos;

public:
    GameObject(){};
    virtual ~GameObject(){};
    virtual void draw() = 0;
    virtual void step(const float dt) = 0;
    virtual void event(const SDL_Event &e) = 0;
};