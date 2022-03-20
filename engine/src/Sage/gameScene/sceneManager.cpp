#include "sceneManager.hpp"
#include "gameSceneFactory.hpp"


sceneManager* sceneManager::get(){
    static sceneManager instance;
    return &instance;
}

sceneManager::sceneManager(){
    currentSceneName = (scenes)0;
    setSceneFromName();
    running = true;
}

void sceneManager::setSceneFromName(){
    currentScene = GameSceneFactory::get() -> createScene(currentSceneName);
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

void sceneManager::handle_event(const SDL_Event &e){
    if (e.type == SDL_QUIT){
        stopGame();
    }
    currentScene -> on_event(e);
}

void sceneManager::handle_step(){
    float deltaTime = (SDL_GetTicks() - ticksCount) / 1000.0f;
    if (deltaTime > 0.5){
        deltaTime = 0.5f;
    }
    ticksCount = SDL_GetTicks();
    currentScene -> on_step(deltaTime);
}

void sceneManager::quit(){
    delete currentScene;
}

void sceneManager::changeCurrentScene(scenes newScene){
    delete currentScene;
    currentScene = GameSceneFactory::get() -> createScene(newScene);
    currentSceneName = newScene;
}

void sceneManager::stopGame(){
    running = false;
}

