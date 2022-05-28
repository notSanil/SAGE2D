#pragma once
#include <string>

#include "Sage/transform/point.hpp"
#include "Sage/Core/Window.h"
#include "Sage/texture/Texture.hpp"
#include "Sage/transform/Vec4.h"
#include "Sage/transform/Transform.h"

class Renderer {
private:
    Renderer();

public:
    static void init(Sage::Window* window);
    static void destroy();

    static void StartScene();
    static void EndScene();

    //static void RenderText(const Font* font, std::string const& text, Sage::Vec4 const& col, Point const pos);
    static void RenderTexture(Sage::Texture* texture, Point pos, Point dims, Sage::Vec4<int> color = {255, 255, 255, 255});
    static void RenderTexture(Sage::Texture* texture, Sage::Vec4<int> texSize, Sage::Vec4<int> destSize, Sage::Vec4<int> color = { 255, 255, 255, 255 });
    static void RenderTexture(Sage::Texture* texture, Sage::Vec4<int> texSize, Sage::Transform& transform, Sage::Vec4<int> color = { 255, 255, 255, 255 });
    static void RenderRotatedTexture(Sage::Texture* texture, Sage::Vec4<int> texSize, Sage::Transform& transform, Sage::Vec4<int> color = { 255, 255, 255, 255 });
    static void RenderRect(Point pos, Point dims, int r, int g, int b);
};
