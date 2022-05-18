#include "sceneManager.hpp"


void sceneManager::quit(){
    delete currentScene;
    currentScene = nullptr;
}

GameScene* sceneManager::currentScene = nullptr;
