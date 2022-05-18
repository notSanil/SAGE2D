#pragma once

#include "gameScene.hpp"

class sceneManager{
private:
    static GameScene *currentScene;
    sceneManager();

public:
    template <typename T>
    static void changeCurrentScene()
    {
        delete currentScene;
        currentScene = nullptr;
        currentScene = new T;
    }
    static GameScene* getCurrentScene() { return currentScene; };
    static void quit();
};
