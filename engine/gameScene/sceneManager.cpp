#include "sceneManager.hpp"

sceneManager::sceneManager(){
    currentSceneName = (scenes)0;
    setSceneFromName();
    running = true;
}

void sceneManager::setSceneFromName(){
    currentScene = factory -> createScene(currentSceneName);
}

void sceneManager::run(){
    SDL_Event e;
    while (running){
        while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksCount + timePerFrame));

        while (SDL_PollEvent(&e) != 0){
            handle_event(e);
        }
        handle_step();
        currentScene -> on_render();
    }

    quit();
}

void sceneManager::handle_event(SDL_Event &e){
    if (e.type == SDL_QUIT){
        running = false;
    }
    currentScene -> on_event(e);
}

void sceneManager::handle_step(){
    float deltaTime = (SDL_GetTicks() - ticksCount) / 1000.0f;
    ticksCount = SDL_GetTicks();
    currentScene -> on_step();
}

void sceneManager::changeCurrent(scenes newScene){
    delete currentScene;
    currentScene = factory -> createScene(newScene);
    currentSceneName = newScene;
    std::cout << "Scene Changed to " << (int)currentSceneName << "\n";
}

void sceneManager::quit(){
    delete currentScene;
}

sceneManager* sceneManager::get(){
    static sceneManager instance;
    return &instance;
}
