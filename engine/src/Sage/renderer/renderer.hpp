#pragma once
#include <string>

#include <glm/glm.hpp>
#include "Sage/Core/Window.h"
#include "Sage/texture/Texture.hpp"
#include "Sage/renderer/Shader.h"
#include "RenderAPI.h"

namespace Sage {
    class Renderer
    {
    private:
        Renderer();

    public:
        static void init(Window* window);
        static void destroy();

        static void StartScene();
        static void EndScene();

        //static void RenderText(const Font* font, std::string const& text, Vec4 const& col, Point const pos);
        static void RenderTexture(Texture* texture, glm::ivec2 pos, glm::ivec2 dims, glm::ivec4 color = { 255, 255, 255, 255 });
        static void RenderTexture(Texture* texture, glm::ivec4 texSize, glm::ivec4 destSize, glm::ivec4 color = { 255, 255, 255, 255 });
        static void RenderTexture(Texture* texture, glm::ivec4 texSize, glm::imat3x2& transform, glm::ivec4 color = { 255, 255, 255, 255 });
        static void RenderRotatedTexture(Texture* texture, glm::ivec4 texSize, glm::imat3x2& transform, glm::ivec4 color = { 255, 255, 255, 255 });
        static void RenderRect(glm::vec2 pos, glm::vec2 dims, float r, float g, float b);

    private:
        static std::unique_ptr<RenderAPI> renderAPI;
        static std::unique_ptr<VertexArray> vao;
        static std::unique_ptr<VertexBuffer> vertexBuffer;
        static std::unique_ptr<IndexBuffer> indexBuffer;

        static std::unique_ptr<Shader> shader;
    };
}

