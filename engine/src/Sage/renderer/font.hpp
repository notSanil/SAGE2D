#if 0

#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include <SDL_ttf.h>

#include "Sage/transform/point.hpp"

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

    SDL_Texture* create_glyph(int alphabet, TTF_Font* font);
    Font(const std::string &path, int size);
};

#endif