#include "renderer.hpp"

#include "Sage/Core/Log.h"
#include "Platform/SDL/SdlRenderer.h"
#include "Platform/SDL/SdlTexture.h"
#include "Platform/Windows/WindowsWindow.h"
#include "Sage/transform/Vec4.h"

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

void Renderer::RenderText(const Font *font, std::string const &text, Sage::Vec4 const &col, Point pos)
{
    Sage::SdlRenderer::RenderText(font, text, col, pos);
}

void Renderer::RenderTexture(Sage::Texture* texture, Point pos, Point dims)
{
    Sage::SdlRenderer::RenderTexture((Sage::SdlTexture*)texture, pos, dims);
}

void Renderer::RenderTexture(Sage::Texture* texture, Sage::Vec4 texSize, Sage::Vec4 destSize)
{
    Sage::SdlRenderer::RenderTexture((Sage::SdlTexture*)texture, texSize, destSize);
}

void Renderer::RenderRect(Point pos, Point dims, int r, int g, int b)
{
    Sage::SdlRenderer::RenderRect(pos, dims, r, g, b);
}

void Renderer::destroy(){
    Sage::SdlRenderer::destroy();
}
