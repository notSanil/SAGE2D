#pragma once

#include "../../engine/gameObject/gameObject.hpp"
#include "../../engine/animator/animator.hpp"
#include "../../engine/transform/point.hpp"


class Dummy : public GameObject{
private:
    Animator animator = Animator("src/assets/images/alien.png");

public:
    Dummy(Point const pos){
        this -> pos = pos;
        animator.setFrameColumnsRows(6, 4);
    }

    void draw() override{
        animator.renderCurrentFrameWithCamera(pos);
        animator.nextFrame();
    }

    void step(float deltaTime) override{
    }

    void event() override{
    }

    static __stdcall GameObject* CreateObjectFn(Point const pos){
        return new Dummy(pos);
    }

    ~Dummy() override{
        animator.free();
    }
};
