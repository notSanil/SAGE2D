#include "renderer.hpp"

#include "Sage/Core/Log.h"
#include "Platform/SDL/SdlRenderer.h"
#include "Platform/Windows/WindowsWindow.h"

void Renderer::init(Sage::Window* window)
{
    Sage::SdlRenderer::init((Sage::WindowsWindow*)window);
}

Renderer::Renderer(){};

SDL_Renderer* Renderer::GetSDLRenderer()
{
    return Sage::SdlRenderer::GetSDLRenderer();
}

void Renderer::StartScene()
{
    Sage::SdlRenderer::StartScene();
}

void Renderer::EndScene()
{
    Sage::SdlRenderer::EndScene();
}

void Renderer::RenderText(const Font *font, std::string const &text, SDL_Color const &col, Point pos)
{
    Sage::SdlRenderer::RenderText(font, text, col, pos);
}

void Renderer::RenderTexture(SDL_Texture* texture, Point pos, Point dims)
{
    Sage::SdlRenderer::RenderTexture(texture, pos, dims);
}

void Renderer::RenderTexture(SDL_Texture* texture, SDL_Rect texSize, SDL_Rect destSize)
{
    Sage::SdlRenderer::RenderTexture(texture, texSize, destSize);
}

void Renderer::RenderRect(Point pos, Point dims, int r, int g, int b)
{
    Sage::SdlRenderer::RenderRect(pos, dims, r, g, b);
}

void Renderer::destroy(){
    Sage::SdlRenderer::destroy();
}
