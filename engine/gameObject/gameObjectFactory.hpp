#pragma once
#include <unordered_map>

#include "gameObject.hpp"
#include "../transform/point.hpp"
#include "../gameScene/gameScene.hpp"

enum class objects{
    dummy,
};

typedef GameObject* (__stdcall *CreateObjectFn) (Point);

class GameObjectFactory{
private:
    GameObjectFactory(){};

    typedef std::unordered_map<objects, CreateObjectFn> objMap;
    objMap FactoryMap;

public:
    static GameObjectFactory* get(){
        static GameObjectFactory instance;
        return &instance;
    }    
    
    void registerObject(objects const object, CreateObjectFn const func){
        FactoryMap[object] = func;
    }

    GameObject* create(objects const object, Point const pos){
        auto it = FactoryMap.find(object);
        if (it != FactoryMap.end()){
            return it -> second(pos);
        }

        return NULL;
    }
};
