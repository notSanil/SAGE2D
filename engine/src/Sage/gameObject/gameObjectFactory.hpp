#pragma once
#include <unordered_map>

#include "gameObject.hpp"
#include "Sage/transform/point.hpp"

enum class objects{
    dummy,
    texTest
};

typedef GameObject* (__stdcall *CreateObjectFn) (Point);

class GameObjectFactory{
private:
    typedef std::unordered_map<objects, CreateObjectFn> objMap;
    objMap FactoryMap;
    
    GameObjectFactory();

public:
    static GameObjectFactory* get();    
    void registerObject(objects const object, const CreateObjectFn func);
    GameObject* create(objects const object, Point const pos);
};
