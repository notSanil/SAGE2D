#pragma once
#include <memory>
#include <glm/glm.hpp>
#include "Sage/Core/Window.h"
#include "Sage/renderer/VertexArray.h"

namespace Sage {
    enum class API
    {
        None = 0,
        SDL = 1,
        OpenGL = 2,
    };

    class RenderAPI
    {
    public:
        virtual void Init(Window* window) = 0;
        virtual void Shutdown() = 0;

        virtual void SetViewport(int x, int y, int width, int height) = 0;
        virtual void SetClearColor(glm::vec4 color) = 0;
        virtual void ClearScreen() = 0;
        virtual void SetUniformMat4(uint32_t location, glm::mat4& matrix) = 0;

        virtual void Draw(VertexArray* vertexArray) = 0;

        static API GetApi() { return currentApi; }
        static std::unique_ptr<RenderAPI> Create();
    private:
        static API currentApi;
    };
}