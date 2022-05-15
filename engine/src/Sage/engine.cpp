#include "engine.hpp"

#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Sage/exceptions/sdlException.hpp"

#include "Sage/renderer/renderer.hpp"
#include "Sage/gameScene/sceneManager.hpp"
#include "Sage/texture/texture.hpp"

Engine::Engine(int const width, int const height, const std::string &name): 
wWidth(width), 
wHeight(height),
gameName(name){
    initialiseSDL();
    gameWindow = createWindow();
	initialiseComponents();
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
}

void Engine::startGame(){

}

Engine::~Engine(){
    SDL_DestroyWindow(gameWindow);
    Renderer::destroy();
    Font::freeAllFonts();
    Texture::destroyAllTextures();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}