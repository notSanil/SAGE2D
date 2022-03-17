#pragma once
#include <string>

#include <SDL2/SDL.h>


class Engine{
public:
    Engine(int const width, int const height, const std::string &name);
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