#pragma once
#include "Sage/Sage.h"

class Level1: public GameScene{
private:
    Font* font = nullptr;

public:
    Level1();
    static  GameScene* __stdcall CreateSceneFn();
    void on_step(const float deltaTime) override;
    void on_render() override;
    void on_event(const SDL_Event &e) override;
    ~Level1();
};