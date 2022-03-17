#pragma once
#include "Sage/gameScene/gameScene.hpp"
#include "Sage/renderer/renderer.hpp"
#include "Sage/renderer/text_renderer.hpp"

class Level1: public GameScene{
private:
    Font* font = Font::get("game/assets/fonts/Roboto-Regular.ttf", 24);
    TextRenderer* tr = TextRenderer::get();

public:
    Level1();
    static  GameScene* __stdcall CreateSceneFn();
    void on_step(const float deltaTime) override;
    void on_render() override;
    void on_event(const SDL_Event &e) override;
    ~Level1();
};