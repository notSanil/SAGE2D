#pragma once
#include <unordered_map>

#include "Sage/gameScene/gameScene.hpp"

enum class scenes{
    SPLASH,
    LEVEL1
};

typedef GameScene* (__stdcall *CreateInstanceFn) (void);

class GameSceneFactory{
private:
    typedef std::unordered_map<scenes, CreateInstanceFn> SceneMap;
    SceneMap FactoryMap;
    
    GameSceneFactory();

public:
    static GameSceneFactory* get();    
    void Register(scenes const scene, const CreateInstanceFn create);
    GameScene* createScene(const scenes scene);
    ~GameSceneFactory();
};