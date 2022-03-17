#pragma once
#include <SDL2/SDL.h>

#include "Sage/transform/point.hpp"
#include "Sage/texture/texture.hpp"

class Animator{
private:
    SDL_Texture* texMap = nullptr;

    SDL_Rect frameSize{0, 0, 0, 0};
    SDL_Rect texSize{0, 0, 0, 0};
    SDL_Rect renderPosition{0, 0, 0, 0};

    int cols = 1, rows = 1;
    int currentFrame = 0;
    

public:
    Animator(const std::string &texMapPath);
    void renderCurrentFrame(Point const &pos);
    void renderCurrentFrameWithCamera(Point const &pos);
    void setFrameColumnsRows(int const totalColumns, int const totalRows);
    void loadAndSetTexMap(std::string const &path);
    void moveToNextFrame();
};