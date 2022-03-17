#pragma once

#include "Sage/gameObject/gameObject.hpp"

class TextureTest : public GameObject
{
public:
    TextureTest(Point pos);
    virtual ~TextureTest();
    virtual void draw() override;
    virtual void step(const float dt) override;
    virtual void event(const SDL_Event &e) override;

    static GameObject* __stdcall CreateObjectFn(Point const pos);

private:
    SDL_Texture* texture = nullptr;
};