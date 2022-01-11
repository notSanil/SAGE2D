#pragma once
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "exceptions/sdlException.hpp"

#include "renderer/renderer.hpp"
#include "gameScene/gameSceneFactory.hpp"
#include "gameObject/gameObjectFactory.hpp"
#include "gameScene/sceneManager.hpp"

#include "../game/scenes/level1.hpp"
#include "../game/scenes/splash.hpp"

#include "../game/objects/test.hpp"

class Engine{
public:
    Engine(int const width, int const height, std::string const &name);
    ~Engine();

private:
    int wWidth, wHeight;
    std::string gameName;
    SDL_Window* gameWindow;

    void initialiseSDL();
    SDL_Window* createWindow();
    void initialiseComponents();
    void initialiseSceneFactory();
    void initialiseObjectFactory();
    void startGame();

};