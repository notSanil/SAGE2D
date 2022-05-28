#include "text_renderer.hpp"
#include "Sage/renderer/renderer.hpp"

TextRenderer* TextRenderer::get(){
    static TextRenderer instance;
    return &instance;
}

TextRenderer::TextRenderer(){};

void TextRenderer::renderText(const Font *font, std::string const &text, Sage::Vec4<int> col, Point const pos){
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
        //TODO: Instead of making individual glyphs, need to construct 
        // a single texture that will contain all text data
        //Renderer::RenderTexture(glyph, Point{lastPos.x, lastPos.y}, {w, h});
        lastPos.x += w;
    }
}
