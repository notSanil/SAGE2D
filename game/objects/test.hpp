#pragma once

#include "Sage/gameObject/gameObject.hpp"
#include "Sage/animator/animator.hpp"
#include "Sage/transform/point.hpp"


class Dummy : public GameObject{
private:
    Animator animator = Animator("game/assets/images/alien.png");

public:
    Dummy(Point const pos);
    void draw() override;
    void step(const float deltaTime) override;
    void event(const SDL_Event &e) override;
    static GameObject* __stdcall CreateObjectFn(Point const pos);
    ~Dummy() override;
};
