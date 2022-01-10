#include "gameSceneFactory.hpp"


GameSceneFactory::GameSceneFactory(){};

GameSceneFactory::~GameSceneFactory(){
    FactoryMap.clear();
}

GameSceneFactory* GameSceneFactory::get(){
    static GameSceneFactory instance;
    return &instance;
}

void GameSceneFactory::Register(scenes const scene, CreateInstanceFn const create){
    FactoryMap[scene] = create;
}

GameScene* GameSceneFactory::createScene(const scenes scene){
    auto it = FactoryMap.find(scene);
    if (it != FactoryMap.end())
        return it -> second();
    
    //This should ideally return an exception
    return NULL;
}
