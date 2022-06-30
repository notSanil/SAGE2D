#pragma once
#include <string>

#include <glm/glm.hpp>
#include "Sage/Core/Window.h"
#include "Sage/Core/Camera.h"
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
        static void StartScene(Camera& camera);
        static void EndScene();

        //static void RenderText(const Font* font, std::string const& text, Vec4 const& col, Point const pos);
        static void RenderTexture(Texture* texture, const glm::vec2& pos, const glm::vec2& dims, const glm::vec4& color = { 1, 1, 1, 1 });
        static void RenderTexture(Texture* texture, const glm::vec4& texSize, const glm::vec4& destSize, const glm::vec4& color = { 1, 1, 1, 1 });
        static void RenderTexture(Texture* texture, const glm::vec4& texSize, const glm::mat3& transform, const glm::vec4& color = { 1, 1, 1, 1 });
        static void RenderRotatedTexture(Texture* texture, const glm::vec4& texSize, const glm::mat3& transform, const glm::vec4& color = { 1, 1, 1, 1 });
        static void RenderTexture(Texture* texture, const glm::mat3& textureTransform, const glm::mat3& transform, const glm::vec4& color = { 1, 1, 1, 1 });
        static void RenderRect(const glm::vec2& pos, const glm::vec2& dims, const glm::vec4& color);

    private:
        static std::unique_ptr<RenderAPI> renderAPI;
        static std::unique_ptr<VertexArray> vao;
        static std::unique_ptr<VertexBuffer> vertexBuffer;
        static std::unique_ptr<IndexBuffer> indexBuffer;

        static std::unique_ptr<Shader> shader;
    };
}

