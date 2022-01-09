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

    SDL_Texture* create_glyph(int alphabet, TTF_Font* font){
        SDL_Color col{255, 255, 255};
        SDL_Surface* text = TTF_RenderGlyph_Blended(font, alphabet, col);
        SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text);
        SDL_FreeSurface(text);
        return text_texture;
    }

    Font(std::string path, int size): path(path){
        glyphs.reserve(128);
        TTF_Font* font = TTF_OpenFont(path.c_str(), size);
        for (int i = 0; i < 128;++i){
            glyphs.push_back(create_glyph(i, font));
        }
        TTF_CloseFont(font);
    }

public:
    SDL_Texture* getGlyph(int const ind) const{
        return glyphs.at(ind);
    }

    static Font* get(std::string path, int size){
        auto location = loadedFonts.find(path);
        if (location != loadedFonts.end()){
            Font* font = loadedFonts.at(path);
            return font;
        }

        Font* newFont = new Font(path, size);
        loadedFonts[path] = newFont;
        return newFont;
    }

    void free(){
        for (auto &glyph: glyphs){
            SDL_DestroyTexture(glyph);
        }

        auto it = loadedFonts.find(path);
        if(it != loadedFonts.end()){
            delete loadedFonts.at(path);
            loadedFonts.erase(it);
        }
    }
};

std::unordered_map<std::string, Font*> Font::loadedFonts;

class TextRenderer{
private:
    SDL_Renderer* renderer = Renderer::get();

    TextRenderer(){};

public:
    void renderText(Font* const font, std::string const text, SDL_Color const col, Point const pos){
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

    static TextRenderer* get(){
        static TextRenderer instance;
        return &instance;
    }
};
