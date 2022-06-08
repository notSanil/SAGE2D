#include "renderer.hpp"

#include "Sage/Core/Log.h"
#include "Platform/SDL/SdlRenderer.h"
#include "Platform/SDL/SdlTexture.h"
#include "Platform/Windows/WindowsWindow.h"

void Renderer::init(Sage::Window* window)
{
    Sage::SdlRenderer::init((Sage::WindowsWindow*)window);
}

Renderer::Renderer(){};

void Renderer::StartScene()
{
    Sage::SdlRenderer::StartScene();
}

void Renderer::EndScene()
{
    Sage::SdlRenderer::EndScene();
}

//void Renderer::RenderText(const Font *font, std::string const &text, Sage::Vec4 const &col, Point pos)
//{
//    Sage::SdlRenderer::RenderText(font, text, col, pos);
//}

void Renderer::RenderTexture(Sage::Texture* texture, glm::ivec2 pos, glm::ivec2 dims, glm::ivec4 color)
{
    Sage::SdlRenderer::RenderTexture((Sage::SdlTexture*)texture, pos, dims, color);
}

void Renderer::RenderTexture(Sage::Texture* texture, glm::ivec4 texSize, glm::ivec4 destSize, glm::ivec4 color)
{
    Sage::SdlRenderer::RenderTexture((Sage::SdlTexture*)texture, texSize, destSize, color);
}

void Renderer::RenderTexture(Sage::Texture* texture, glm::ivec4 texSize, glm::imat3x2& transform, glm::ivec4 color)
{
    Sage::SdlRenderer::RenderTexture((Sage::SdlTexture*)texture, texSize, transform, color);
}

void Renderer::RenderRotatedTexture(Sage::Texture* texture, glm::ivec4 texSize, glm::imat3x2& transform, glm::ivec4 color)
{
    Sage::SdlRenderer::RenderRotatedTexture((Sage::SdlTexture*)texture, texSize, transform, color);
}

void Renderer::RenderRect(glm::ivec2 pos, glm::ivec2 dims, int r, int g, int b)
{
    Sage::SdlRenderer::RenderRect(pos, dims, r, g, b);
}

void Renderer::destroy(){
    Sage::SdlRenderer::destroy();
}
