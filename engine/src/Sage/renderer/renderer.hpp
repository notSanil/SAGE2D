#pragma once
#include <string>

#include "Sage/transform/point.hpp"
#include "Sage/renderer/font.hpp"
#include "Sage/Core/Window.h"

class Renderer {
private:
    Renderer();

public:
    static void init(Sage::Window* window);
    static void destroy();

    static SDL_Renderer* GetSDLRenderer();

    static void StartScene();
    static void EndScene();

    static void RenderText(const Font* font, std::string const& text, SDL_Color const& col, Point const pos);
    static void RenderTexture(SDL_Texture* texture, Point pos, Point dims);
    static void RenderTexture(SDL_Texture* texture, SDL_Rect texSize, SDL_Rect destSize);
    static void RenderRect(Point pos, Point dims, int r, int g, int b);
};
