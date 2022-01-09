#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "../engine/exceptions/sdlException.hpp"
#include "../engine/renderer/renderer.hpp"
#include "../engine/gameScene/sceneManager.hpp"
#include "../engine/gameScene/gameSceneFactory.hpp"
#include "../engine/gameObject/gameObjectFactory.hpp"

#include "../game/scenes/splash.hpp"
#include "../game/scenes/level1.hpp"

#include "../game/objects/test.hpp"

void initialise_sdl(){
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        throw SDLException(SDL_Uninitialised);
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)){
        throw SDLException(Image_Failed);
    }

    if (TTF_Init() < 0){
        throw SDLException(Font_Failed);
    }
}

void initialise_factory(){
    GameSceneFactory* f = GameSceneFactory::get();
    f -> Register(scenes::SPLASH, &splash::CreateSceneFn);
    f -> Register(scenes::LEVEL1, &Level1::CreateSceneFn);
}

void initialiseObjectFactory(){
    GameObjectFactory* f = GameObjectFactory::get();
    f -> registerObject(objects::dummy, &Dummy::CreateObjectFn);
}

int main(int argv, char **argc){
    initialise_sdl();

    SDL_Window *window = NULL;
    const int WIDTH = 600, HEIGHT = 600; 
    const std::string windowName = "Game Engine";
    window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL){
        throw SDLException(Window_Failed);
    }

    Renderer::init(window);    
    
    initialise_factory();
    initialiseObjectFactory();

    sceneManager *manager = sceneManager::get();
    manager -> run();

    SDL_DestroyWindow(window);
    Renderer::destroy();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    return 0;
}