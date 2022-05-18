#pragma once
#include <string>

#include "Sage/transform/point.hpp"
#include "Sage/renderer/font.hpp"
#include "Sage/Core/Window.h"
#include "Sage/texture/texture.hpp"
#include "Sage/transform/Vec4.h"

class Renderer {
private:
    Renderer();

public:
    static void init(Sage::Window* window);
    static void destroy();

    //Temp
    static SDL_Renderer* GetSDLRenderer();

    static void StartScene();
    static void EndScene();

    static void RenderText(const Font* font, std::string const& text, Sage::Vec4 const& col, Point const pos);
    static void RenderTexture(Sage::Texture* texture, Point pos, Point dims);
    static void RenderTexture(Sage::Texture* texture, Sage::Vec4 texSize, Sage::Vec4 destSize);
    static void RenderRect(Point pos, Point dims, int r, int g, int b);
};
