#pragma once

#include "gameScene.hpp"
#include "gameSceneFactory.hpp"

class sceneManager{
private:
    scenes currentSceneName;
    GameScene *currentScene;
    
    Uint32 ticksCount = 0;
    int targetFrameRate = 24;
    float timePerFrame = 1000.0f / targetFrameRate;
    bool running = false;

    sceneManager();    
    void setSceneFromName();
    GameSceneFactory *factory = GameSceneFactory::get();
    void quit();
    void handle_event(SDL_Event &e);
    void handle_step();

public:
    static sceneManager* get();
    void run();
    void changeCurrent(scenes newScene);

};
