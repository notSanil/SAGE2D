#include "font.hpp"
#include "Sage/renderer/renderer.hpp"

Font* Font::get(std::string const &path, int const size){
    auto location = loadedFonts.find(path);
    if (location != loadedFonts.end()){
        return location -> second;
    }

    Font* newFont = new Font(path, size);
    loadedFonts[path] = newFont;
    return newFont;
}

Font::Font(const std::string &path, int size): path(path){
    glyphs.reserve(128);
    TTF_Font* font = TTF_OpenFont(path.c_str(), size);
    for (int i = 0; i < 128;++i){
        glyphs.push_back(create_glyph(i, font));
    }
    TTF_CloseFont(font);
}

SDL_Texture* Font::create_glyph(int alphabet, TTF_Font* font){
    SDL_Color col{255, 255, 255};
    SDL_Surface* text = TTF_RenderGlyph_Blended(font, alphabet, col);
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(Renderer::GetSDLRenderer(), text);
    SDL_FreeSurface(text);
    return text_texture;
}

SDL_Texture* Font::getGlyph(int const ind) const{
    return glyphs.at(ind);
}

void Font::free(){
    for (auto &glyph: glyphs){
        SDL_DestroyTexture(glyph);
    }

    auto it = loadedFonts.find(path);
    if(it != loadedFonts.end()){
        delete loadedFonts.at(path);
        loadedFonts.erase(it);
    }
}

void Font::freeAllFonts(){
    for (auto &element: loadedFonts){
        element.second -> free();
    }
    loadedFonts.clear();
}
std::unordered_map<std::string, Font*> Font::loadedFonts;