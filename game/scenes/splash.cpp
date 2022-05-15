#include "splash.hpp"

#include "level1.hpp"
#include "objects/test.hpp"


splash::splash(){
    GameObject* test = new Dummy(Point{500, 0});
    GameObject* test2 = new Dummy(Point{500, 300});
    objects.push_back(test2);
    objects.push_back(test);

    for (int i = 0; i < 5000; ++i){
        GameObject* obj = new Dummy(Point(i / 600, i % 600));
        objects.push_back(obj);
    }
}

void splash::on_render(){
    Renderer::StartScene();

    for (auto &object: objects){
        object -> draw();
    }
    Renderer::EndScene();
}

void splash::on_event(const SDL_Event &e){
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
            sceneManager::get() -> changeCurrentScene<Level1>();
            break;

        case SDLK_i:
            cam -> moveTo(Point(800, 800));
            break;
        
        default:
            break;
        }
    }
}

void splash::on_step(const float deltaTime){
}

splash::~splash(){
    for (auto &object: objects){
        delete object;
    }
    objects.clear();
    Camera::destroyCamera();
}
