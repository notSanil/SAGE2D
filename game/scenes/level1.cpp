#include "level1.hpp"


Level1::Level1(){
    renderer = Renderer::get();
    SDL_GetRendererOutputSize(renderer, &dispWidth, &dispHeight);
};

GameScene* __stdcall Level1::CreateSceneFn(){
    return new Level1;
}

void Level1::on_step(){    
}

void Level1::on_render(){
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);
    tr -> renderText(font, "Hello", SDL_Color{255, 255, 255}, Point(10, 10));
    SDL_RenderPresent(renderer);
}

void Level1::on_event(SDL_Event &e){    
}

void Level1::on_exit(){    
}

Level1::~Level1(){
    for (auto object: objects){
        delete object;
    }
    font -> free();
}
