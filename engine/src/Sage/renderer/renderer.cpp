#include "renderer.hpp"

#include "Sage/renderer/text_renderer.hpp"
#include "Sage/Core/Log.h"


void Renderer::init(SDL_Window *window){
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer){
        SAGE_CORE_CRIT("Renderer Failed to initialise!");
    }
}

Renderer::Renderer(){};

SDL_Renderer* Renderer::GetSDLRenderer()
{
    return renderer;
}

void Renderer::StartScene()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void Renderer::EndScene()
{
    SDL_RenderPresent(renderer);
}

void Renderer::RenderText(const Font *font, std::string const &text, SDL_Color const &col, Point const pos)
{
    TextRenderer::get()->renderText(font, text, col, pos);
}

void Renderer::RenderTexture(SDL_Texture* texture, Point pos, Point dims)
{
    SDL_Rect dest{pos.x, pos.y, dims.x, dims.y};
    SDL_RenderCopy(renderer, texture, NULL, &dest);
}

void Renderer::RenderTexture(SDL_Texture* texture, SDL_Rect texSize, SDL_Rect destSize)
{
    SDL_RenderCopy(renderer, texture, &texSize, &destSize);
}

void Renderer::RenderRect(Point pos, Point dims, int r, int g, int b)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_Rect dest{pos.x, pos.y, dims.x, dims.y};
    SDL_RenderDrawRect(renderer, &dest);
}

void Renderer::destroy(){
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
}
SDL_Renderer* Renderer::renderer = nullptr;
