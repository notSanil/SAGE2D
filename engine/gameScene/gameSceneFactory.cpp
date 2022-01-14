#include "gameSceneFactory.hpp"


GameSceneFactory* GameSceneFactory::get(){
    static GameSceneFactory instance;
    return &instance;
}

GameSceneFactory::GameSceneFactory(){};

void GameSceneFactory::Register(scenes const scene, const CreateInstanceFn create){
    FactoryMap[scene] = create;
}

GameScene* GameSceneFactory::createScene(const scenes scene){
    auto it = FactoryMap.find(scene);
    if (it != FactoryMap.end())
        return it -> second();
    
    //This should ideally return an exception
    return NULL;
}

GameSceneFactory::~GameSceneFactory(){
    FactoryMap.clear();
}