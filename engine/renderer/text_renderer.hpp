#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include <SDL2/SDL_ttf.h>

#include "../transform/point.hpp"
#include "renderer.hpp"

class Font{
private:
    static std::unordered_map<std::string, Font*> loadedFonts;

    std::vector<SDL_Texture*> glyphs;
    SDL_Renderer* renderer = Renderer::get();
    std::string path;

    SDL_Texture* create_glyph(int alphabet, TTF_Font* font);
    Font(std::string path, int size);

public:
    SDL_Texture* getGlyph(int const ind) const;
    static Font* get(std::string path, int size);
    void free();
};

class TextRenderer{
private:
    SDL_Renderer* renderer = Renderer::get();
    TextRenderer();

public:
    void renderText(Font* const font, std::string const text, SDL_Color const col, Point const pos);
    static TextRenderer* get();
};
