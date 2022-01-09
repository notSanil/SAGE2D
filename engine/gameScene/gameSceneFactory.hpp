#pragma once
#include <unordered_map>

#include "gameScene.hpp"

enum class scenes{
    SPLASH,
    LEVEL1
};

typedef GameScene* (__stdcall *CreateInstanceFn) (void);

class GameSceneFactory{
private:
    GameSceneFactory(){};

    typedef std::unordered_map<scenes, CreateInstanceFn> SceneMap;
    SceneMap FactoryMap;

public:
    ~GameSceneFactory(){
        FactoryMap.clear();
    }

    static GameSceneFactory* get(){
        static GameSceneFactory instance;
        return &instance;
    }
    
    void Register(scenes const scene, CreateInstanceFn const create){
        FactoryMap[scene] = create;
    }

    GameScene* createScene(const scenes scene){
        auto it = FactoryMap.find(scene);
        if (it != FactoryMap.end())
            return it -> second();
        
        //This should ideally return an exception
        return NULL;
    }
};