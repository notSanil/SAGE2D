#pragma once
#include <string>

#include "Sage/Core/Window.h"
#include "Sage/texture/Texture.hpp"
#include <glm/glm.hpp>

class Renderer {
private:
    Renderer();

public:
    static void init(Sage::Window* window);
    static void destroy();

    static void StartScene();
    static void EndScene();

    //static void RenderText(const Font* font, std::string const& text, Sage::Vec4 const& col, Point const pos);
    static void RenderTexture(Sage::Texture* texture, glm::ivec2 pos, glm::ivec2 dims, glm::ivec4 color = {255, 255, 255, 255});
    static void RenderTexture(Sage::Texture* texture, glm::ivec4 texSize, glm::ivec4 destSize, glm::ivec4 color = { 255, 255, 255, 255 });
    static void RenderTexture(Sage::Texture* texture, glm::ivec4 texSize, glm::imat3x2& transform, glm::ivec4 color = { 255, 255, 255, 255 });
    static void RenderRotatedTexture(Sage::Texture* texture, glm::ivec4 texSize, glm::imat3x2& transform, glm::ivec4 color = { 255, 255, 255, 255 });
    static void RenderRect(glm::ivec2 pos, glm::ivec2 dims, int r, int g, int b);
};
