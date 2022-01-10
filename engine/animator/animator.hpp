#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "../renderer/renderer.hpp"
#include "../transform/point.hpp"
#include "../camera/camera.hpp"

class Animator{
private:
    SDL_Texture* texMap = nullptr;
    SDL_Renderer* renderer = nullptr;

    SDL_Rect frameSize{0, 0, 0, 0};
    SDL_Rect texSize{0, 0, 0, 0};
    SDL_Rect renderPosition{0, 0, 0, 0};

    int cols = 0, rows = 0;
    int currentFrame = 0;
    

public:
    Animator(std::string texMapPath);
    void renderCurrentFrame(Point const &pos);
    void renderCurrentFrameWithCamera(Point const &pos);
    void setFrameColumnsRows(int const totalColumns, int const totalRows);
    void loadAndSetTexMap(std::string path);
    void nextFrame();
    void free();
};