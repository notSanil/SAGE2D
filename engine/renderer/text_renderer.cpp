#include "text_renderer.hpp"


Font* Font::get(std::string path, int size){
    auto location = loadedFonts.find(path);
    if (location != loadedFonts.end()){
        return location -> second;
    }

    Font* newFont = new Font(path, size);
    loadedFonts[path] = newFont;
    return newFont;
}

Font::Font(std::string path, int size): path(path){
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
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text);
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
std::unordered_map<std::string, Font*> Font::loadedFonts;


TextRenderer* TextRenderer::get(){
    static TextRenderer instance;
    return &instance;
}

TextRenderer::TextRenderer(){};

void TextRenderer::renderText(Font* const font, std::string const &text, SDL_Color const &col, Point const pos){
    Point lastPos = pos;
    for (int i = 0; i < text.size();++i){
        SDL_Texture* glyph = font -> getGlyph(int(text.at(i)));
        int w, h;
        SDL_QueryTexture(glyph, NULL, NULL, &w, &h);
        
        if (text.at(i) == '\n'){
            lastPos.y += h;
            lastPos.x = pos.x;
            continue;
        }

        SDL_SetTextureColorMod(glyph, col.r, col.g, col.b);
        SDL_Rect dest{lastPos.x, lastPos.y, w, h};
        SDL_RenderCopy(renderer, glyph, NULL, &dest);

        lastPos.x += w;
    }
}
