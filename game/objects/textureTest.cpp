#include "textureTest.hpp"

#include <Sage/texture/texture.hpp>
#include <Sage/renderer/renderer.hpp>
#include <iostream>

TextureTest::TextureTest(Point pos)
{
    this->pos = pos;
    this->texture = Texture::loadTexture("game/assets/images/alien.png");
}

TextureTest::~TextureTest()
{
}

void TextureTest::draw()
{
    Renderer::RenderTexture(texture, Point{10, 10}, {100, 100});
    Renderer::RenderRect({100, 100}, {90, 90}, 200, 100, 100);
}

void TextureTest::step(const float dt)
{
}

void TextureTest::event(const SDL_Event &e)
{
}

GameObject* __stdcall TextureTest::CreateObjectFn(Point const pos)
{
    return new TextureTest(pos);
}