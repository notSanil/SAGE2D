#pragma once

#include "Sage/Sage.h"


class Dummy : public GameObject{
private:
    Animator animator = Animator("assets/images/alien.png");

public:
    Dummy(Point const pos);
    void draw() override;
    void step(const float deltaTime) override;
    virtual void event(const Sage::Event& e) override;
    ~Dummy() override;
};
