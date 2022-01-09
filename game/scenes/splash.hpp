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
    splash(){
        GameObject* test = f -> create(objects::dummy, Point{500, 0});
        GameObject* test2 = f -> create(objects::dummy, Point{500, 300});
        objects.push_back(test2);
        objects.push_back(test);
        
        renderer = Renderer::get();
        SDL_GetRendererOutputSize(renderer, &dispWidth, &dispHeight);
    }

    void on_render() override{
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        for (auto &object: objects){
            object -> draw();
        }
        SDL_RenderPresent(renderer);
    }

    void on_event(SDL_Event &e) override{
        int const speed = 20;
        if (e.type == SDL_KEYDOWN){
            switch (e.key.keysym.sym)
            {
            case SDLK_d:
                cam -> move(Point{speed, 0});
                break;
            
            case SDLK_w:
                cam -> move(Point{0, -speed});
                break;

            case SDLK_a:
                cam -> move(Point{-speed, 0});
                break;
            
            case SDLK_s:
                cam -> move(Point{0, speed});
                break;

            default:
                break;
            }
        }
    }

    void on_step() override{
    }

    void on_exit() override{
    }

    static __stdcall GameScene *CreateSceneFn(){
        return new splash;
    }

    ~splash(){
        for (auto object: objects){
            delete object;
        }
        Camera::destroyCamera();
    }
};