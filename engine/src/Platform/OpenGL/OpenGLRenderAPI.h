#pragma once
#include "Sage/renderer/RenderAPI.h"

namespace Sage {
	class OpenGLRenderAPI : public RenderAPI
	{
    public:
        void Init(Window* window) override;
        void Shutdown() override;

        void SetViewport(int x, int y, int width, int height) override;
        void SetClearColor(glm::vec4 color) override;
        void ClearScreen() override;

        void Draw(VertexArray* vertexArray) override;
	};
}