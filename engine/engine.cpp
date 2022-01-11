#include "engine.hpp"


Engine::Engine(int const width, int const height, std::string const &name): 
wWidth(width), 
wHeight(height),
gameName(name){
    initialiseSDL();
    gameWindow = createWindow();
	initialiseComponents();
    startGame();
}

void Engine::initialiseSDL(){
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

SDL_Window* Engine::createWindow(){
    SDL_Window* win = SDL_CreateWindow(gameName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        wWidth, wHeight, SDL_WINDOW_SHOWN);

	if (win == NULL){
        throw SDLException(Window_Failed);
    }
	return win;
}

void Engine::initialiseComponents(){
	Renderer::init(gameWindow);    
    
    initialiseSceneFactory();
    initialiseObjectFactory();
}

void Engine::initialiseSceneFactory(){
	GameSceneFactory* f = GameSceneFactory::get();
    f -> Register(scenes::SPLASH, &splash::CreateSceneFn);
    f -> Register(scenes::LEVEL1, &Level1::CreateSceneFn);
}

void Engine::initialiseObjectFactory(){
    GameObjectFactory* f = GameObjectFactory::get();
    f -> registerObject(objects::dummy, &Dummy::CreateObjectFn);
}

void Engine::startGame(){
    sceneManager* manager = sceneManager::get();
    manager -> run();
}

Engine::~Engine(){
    SDL_DestroyWindow(gameWindow);
    Renderer::destroy();
    Font::freeAllFonts();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}