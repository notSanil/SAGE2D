#pragma once

#include "Sage/Sage.h"
#include <memory>

class TextureTest : public GameObject
{
public:
    TextureTest(Point pos);
    virtual ~TextureTest();
    virtual void draw() override;
    virtual void step(const float dt) override;
    virtual void event(const Sage::Event& e) override;


private:
    std::shared_ptr<Sage::Texture> texture;
};