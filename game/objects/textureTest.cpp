#include "textureTest.hpp"


TextureTest::TextureTest(Point pos)
{
    this->pos = pos;
    this->texture = Sage::TextureManager::load("assets/images/alien.png");
}

TextureTest::~TextureTest()
{
}

void TextureTest::draw()
{
    Renderer::RenderTexture(texture.get(), Point{10, 10}, {100, 100});
    Renderer::RenderRect({100, 100}, {90, 90}, 200, 100, 100);
}

void TextureTest::step(const float dt)
{
}

void TextureTest::event(const SDL_Event &e)
{
}
