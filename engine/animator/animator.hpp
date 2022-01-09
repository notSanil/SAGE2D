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
    Animator(std::string texMapPath){
        renderer = Renderer::get();
        loadAndSetTexMap(texMapPath);
    }

    void renderCurrentFrame(Point const &pos){
        renderPosition.x = pos.x;
        renderPosition.y = pos.y;
        SDL_RenderCopy(renderer, texMap, &frameSize, &renderPosition);
    }

    void renderCurrentFrameWithCamera(Point const &pos){
        Point gameCoords = Camera::get() -> convertToGameCoords(pos);
        renderPosition.x = gameCoords.x;
        renderPosition.y = gameCoords.y;
        SDL_RenderCopy(renderer, texMap, &frameSize, &renderPosition);
    }

    void setFrameColumnsRows(int const totalColumns, int const totalRows){
        cols = totalColumns;
        rows = totalRows;

        frameSize.w = texSize.w / cols;
        frameSize.h = texSize.h / rows;

        renderPosition.w = frameSize.w;
        renderPosition.h = frameSize.h;
    }

    void loadAndSetTexMap(std::string path){
        SDL_Texture* newTex = NULL;
        newTex = IMG_LoadTexture(renderer, path.c_str());
        if (newTex == NULL){
            std::cout << "The texture was not loaded. " << IMG_GetError();
        }
        
        if (texMap != NULL){
            SDL_DestroyTexture(texMap);
        }
        texMap = newTex;
        
        int w, h;
        SDL_QueryTexture(texMap, NULL, NULL, &w, &h);
        texSize.w = w;
        texSize.h = h;
    }

    void nextFrame(){
        currentFrame = (currentFrame + 1) % (cols * rows);
        int currCol = currentFrame % cols;
        int currRow = currentFrame / cols;

        frameSize.x = currCol * frameSize.w;
        frameSize.y = currRow * frameSize.h;
    }

    void free(){
        SDL_DestroyTexture(texMap);
    }
};