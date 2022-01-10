#pragma once
#include "../../engine/gameScene/gameScene.hpp"
#include "../../engine/gameScene/sceneManager.hpp"
#include "../../engine/renderer/renderer.hpp"
#include "../../engine/transform/point.hpp"
#include "../../engine/camera/camera.hpp"
#include "../../engine/gameObject/gameObjectFactory.hpp"

class splash : public GameScene{
private:
    Camera* cam = Camera::create(Point{800, 800}, Point{600, 600});
    GameObjectFactory* f = GameObjectFactory::get();

public:
    splash();
    void on_render() override;
    void on_event(SDL_Event &e) override;
    void on_step() override;
    void on_exit() override;
    static  GameScene* __stdcall CreateSceneFn();
    ~splash();
};