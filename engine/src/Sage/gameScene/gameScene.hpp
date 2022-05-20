#pragma once

#include "Sage/Events/Event.h"

class GameScene{
public:
    GameScene(){};
    virtual ~GameScene(){};
    virtual void on_render() = 0;
    virtual void on_step(const float dt) = 0;
    virtual void on_event(Sage::Event& e) = 0;
};