#pragma once

#include "Sage/Sage.h"


class Dummy : public GameObject{
private:
    Animator animator = Animator("assets/images/alien.png");

public:
    Dummy(Point const pos);
    void draw() override;
    void step(const float deltaTime) override;
    void event(const SDL_Event &e) override;
    ~Dummy() override;
};
