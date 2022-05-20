#pragma once
#include "Sage/Sage.h"
#include <vector>

class Level1: public GameScene{
private:
    //Font* font = nullptr;
    std::vector <GameObject*> objects;

public:
    Level1();
    void on_step(const float deltaTime) override;
    void on_render() override;
    virtual void on_event(Sage::Event& e) override;
    ~Level1();
};