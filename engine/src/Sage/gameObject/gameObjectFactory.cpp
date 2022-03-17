#include "gameObjectFactory.hpp"


GameObjectFactory::GameObjectFactory(){};

GameObjectFactory* GameObjectFactory::get(){
    static GameObjectFactory instance;
    return &instance;
}    

void GameObjectFactory::registerObject(objects const object, const CreateObjectFn func){
    FactoryMap[object] = func;
}

GameObject* GameObjectFactory::create(objects const object, Point const pos){
    auto it = FactoryMap.find(object);
    if (it != FactoryMap.end()){
        return it -> second(pos);
    }
    return NULL;
}

