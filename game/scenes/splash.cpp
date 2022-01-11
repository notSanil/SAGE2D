#include "splash.hpp"



splash::splash(){
    GameObject* test = f -> create(objects::dummy, Point{500, 0});
    GameObject* test2 = f -> create(objects::dummy, Point{500, 300});
    objects.push_back(test2);
    objects.push_back(test);
    
    renderer = Renderer::get();
    SDL_GetRendererOutputSize(renderer, &dispWidth, &dispHeight);
}

void splash::on_render(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    for (auto &object: objects){
        object -> draw();
    }
    SDL_RenderPresent(renderer);
}

void splash::on_event(SDL_Event &e){
    int const speed = 20;
    if (e.type == SDL_KEYDOWN){
        switch (e.key.keysym.sym)
        {
        case SDLK_d:
            cam -> moveBy(Point{speed, 0});
            break;
        
        case SDLK_w:
            cam -> moveBy(Point{0, -speed});
            break;

        case SDLK_a:
            cam -> moveBy(Point{-speed, 0});
            break;
        
        case SDLK_s:
            cam -> moveBy(Point{0, speed});
            break;

        case SDLK_l:
            sceneManager::get() -> changeCurrentScene(scenes::LEVEL1);
            break;

        case SDLK_i:
            cam -> moveTo(Point(800, 800));
            break;
        
        default:
            break;
        }
    }
}

void splash::on_step(){
}

void splash::on_exit(){
}

GameScene* __stdcall splash::CreateSceneFn(){
    return new splash;
}

splash::~splash(){
    for (auto object: objects){
        delete object;
    }
    Camera::destroyCamera();
}
