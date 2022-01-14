#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include <SDL2/SDL_ttf.h>

#include "../transform/point.hpp"
#include "renderer.hpp"

class Font{
public:
    SDL_Texture* getGlyph(int const ind) const;
    static Font* get(std::string const &path, int const size);
    void free();
    static void freeAllFonts();

private:
    static std::unordered_map<std::string, Font*> loadedFonts;
    std::vector<SDL_Texture*> glyphs;
    std::string path;

    SDL_Renderer* renderer = Renderer::get();
    SDL_Texture* create_glyph(int alphabet, TTF_Font* font);
    Font(const std::string &path, int size);
};

class TextRenderer{
public:
    void renderText(const Font *font, std::string const &text, SDL_Color const &col, Point const pos);
    static TextRenderer* get();

private:
    SDL_Renderer* renderer = Renderer::get();
    TextRenderer();
};
