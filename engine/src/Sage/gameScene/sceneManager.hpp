#pragma once

#include "gameScene.hpp"
#include "gameSceneFactory.hpp"

class sceneManager{
private:
    scenes currentSceneName;
    GameScene *currentScene;
    
    Uint32 ticksCount = 0;
    const int targetFrameRate = 60;
    const float timePerFrame = 1000.0f / targetFrameRate;
    bool running = false;
    
    GameSceneFactory *factory = GameSceneFactory::get();

    sceneManager();    
    void setSceneFromName();
    void quit();
    void handle_event(const SDL_Event &e);
    void handle_step();

public:
    static sceneManager* get();
    void run();
    void changeCurrentScene(scenes newScene);
    void stopGame();
};
