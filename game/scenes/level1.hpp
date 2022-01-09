#pragma once
#include "../../engine/gameScene/gameScene.hpp"
#include "../../engine/renderer/renderer.hpp"

class Level1: public GameScene{
public:
    Level1(){
        renderer = Renderer::get();
        SDL_GetRendererOutputSize(renderer, &dispWidth, &dispHeight);
    };

    static __stdcall GameScene* CreateSceneFn(){
        return new Level1;
    }

    void on_step() override{
        
    }

    void on_render() override{
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_RenderPresent(renderer);
    }

    void on_event(SDL_Event &e) override{
        
    }

    void on_exit() override{
        
    }

    ~Level1(){
        for (auto object: objects){
            delete object;
        }
    }
};