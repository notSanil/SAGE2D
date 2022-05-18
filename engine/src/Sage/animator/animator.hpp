#pragma once
#include "Sage/texture/texture.hpp"
#include "Sage/transform/point.hpp"
#include "Sage/transform/Vec4.h"

class Animator{
private:
    std::shared_ptr<Sage::Texture> texMap;

    Sage::Vec4 frameSize{0, 0, 0, 0};
    Sage::Vec4 renderPosition{0, 0, 0, 0};

    int cols = 1, rows = 1;
    int currentFrame = 0;
    

public:
    Animator(const std::string &texMapPath);
    void renderCurrentFrame(Point pos);
    void renderCurrentFrameWithCamera(Point pos);
    void setFrameColumnsRows(int totalColumns, int totalRows);
    void moveToNextFrame();
};