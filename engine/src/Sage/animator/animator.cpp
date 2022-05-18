#include "animator.hpp"
#include "Sage/camera/camera.hpp"
#include "Sage/renderer/renderer.hpp"

Animator::Animator(const std::string &texMapPath){
    texMap = Sage::TextureManager::load(texMapPath);
}


void Animator::renderCurrentFrame(Point pos){
    renderPosition.x = pos.x;
    renderPosition.y = pos.y;
    Renderer::RenderTexture(texMap.get(), frameSize, renderPosition);
}

void Animator::renderCurrentFrameWithCamera(Point pos){
    Point gameCoords = Camera::get() -> convertToGameCoords(pos);
    renderPosition.x = gameCoords.x;
    renderPosition.y = gameCoords.y;
    Renderer::RenderTexture(texMap.get(), frameSize, renderPosition);
}

void Animator::setFrameColumnsRows(int totalColumns, int totalRows)
{
    cols = totalColumns;
    rows = totalRows;

    frameSize.w = texMap->getWidth() / totalColumns;
    frameSize.h = texMap->getHeight() / totalRows;

    renderPosition.w = frameSize.w;
    renderPosition.h = frameSize.h;
}

void Animator::moveToNextFrame(){
    currentFrame = (currentFrame + 1) % (cols * rows);
    int currCol = currentFrame % cols;
    int currRow = currentFrame / cols;

    frameSize.x = currCol * frameSize.w;
    frameSize.y = currRow * frameSize.h;
}
