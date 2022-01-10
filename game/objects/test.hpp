#pragma once

#include "../../engine/gameObject/gameObject.hpp"
#include "../../engine/animator/animator.hpp"
#include "../../engine/transform/point.hpp"


class Dummy : public GameObject{
private:
    Animator animator = Animator("game/assets/images/alien.png");

public:
    Dummy(Point const pos);
    void draw() override;
    void step(float deltaTime) override;
    void event() override;
    static GameObject* __stdcall CreateObjectFn(Point const pos);
    ~Dummy() override;
};
