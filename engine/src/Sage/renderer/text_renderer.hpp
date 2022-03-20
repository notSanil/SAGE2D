#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include <SDL2/SDL_ttf.h>

#include "Sage/transform/point.hpp"
#include "Sage/renderer/font.hpp"

class TextRenderer{
public:
    void renderText(const Font *font, std::string const &text, SDL_Color const &col, Point const pos);
    static TextRenderer* get();

private:
    TextRenderer();
};
