#pragma once

#include "gameScene.hpp"

class sceneManager{
private:
    GameScene *currentScene = nullptr;
    
    Uint32 ticksCount = 0;
    const int targetFrameRate = 60;
    const float timePerFrame = 1000.0f / targetFrameRate;
    bool running = false;

    sceneManager();
    void quit();
    void handle_event(const SDL_Event &e);
    void handle_step();

public:
    static sceneManager* get();
    void run();

    template <typename T>
    void changeCurrentScene()
    {
        delete currentScene;
        currentScene = new T;
    }

    void stopGame();
};
