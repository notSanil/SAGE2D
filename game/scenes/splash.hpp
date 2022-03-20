#pragma once
#include "Sage/Sage.h"

class splash : public GameScene{
private:
    Camera* cam = Camera::create(Point{800, 800}, Point{600, 600});

public:
    splash();
    void on_render() override;
    void on_event(const SDL_Event &e) override;
    void on_step(const float dt) override;
    static  GameScene* __stdcall CreateSceneFn();
    ~splash();
};