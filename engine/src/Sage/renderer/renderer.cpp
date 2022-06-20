#include "renderer.hpp"

#include "Sage/Core/Log.h"

namespace Sage {
	std::unique_ptr<RenderAPI> Renderer::renderAPI;
	std::unique_ptr<VertexArray> Renderer::vao;
	std::unique_ptr<VertexBuffer> Renderer::vertexBuffer;
	std::unique_ptr<IndexBuffer> Renderer::indexBuffer;

	std::unique_ptr<Shader> Renderer::shader;

	void Renderer::init(Window* window)
	{
		renderAPI = RenderAPI::Create();
		renderAPI->Init(window);
		renderAPI->SetClearColor({ 0, 0, 0, 1 });
		renderAPI->SetViewport(0, 0, window->GetWidth(), window->GetHeight());

		vao = VertexArray::Create();

		vertexBuffer = VertexBuffer::Create(24 * sizeof(float));
		vertexBuffer->SetLayout({ 
			{"pos", DataType::Float2},
			{"color", DataType::Float4}
		});
		vao->AddVertexBuffer(vertexBuffer.get());

		uint32_t indices[] = { 0, 1, 2, 
								2, 3, 0 };
		indexBuffer = IndexBuffer::Create(indices, 6);
		vao->SetIndexBuffer(indexBuffer.get());

		shader = Shader::Create("resources/shaders/VertexShader.glsl", "resources/shaders/FragShader.glsl");
		shader->Bind();
	}

	Renderer::Renderer() 
	{
		
	};

	void Renderer::StartScene()
	{
		renderAPI->ClearScreen();
		shader->Bind();
	}

	void Renderer::EndScene()
	{
	}

	//void Renderer::RenderText(const Font *font, std::string const &text, Vec4 const &col, Point pos)
	//{
	//    SdlRenderer::RenderText(font, text, col, pos);
	//}

	void Renderer::RenderTexture(Texture* texture, glm::ivec2 pos, glm::ivec2 dims, glm::ivec4 color)
	{
		//SdlRenderer::RenderTexture((SdlTexture*)texture, pos, dims, color);
	}

	void Renderer::RenderTexture(Texture* texture, glm::ivec4 texSize, glm::ivec4 destSize, glm::ivec4 color)
	{
		//SdlRenderer::RenderTexture((SdlTexture*)texture, texSize, destSize, color);
	}

	void Renderer::RenderTexture(Texture* texture, glm::ivec4 texSize, glm::imat3x2& transform, glm::ivec4 color)
	{
		//SdlRenderer::RenderTexture((SdlTexture*)texture, texSize, transform, color);
	}

	void Renderer::RenderRotatedTexture(Texture* texture, glm::ivec4 texSize, glm::imat3x2& transform, glm::ivec4 color)
	{
		//SdlRenderer::RenderRotatedTexture((SdlTexture*)texture, texSize, transform, color);
	}

	void Renderer::RenderRect(glm::vec2 pos, glm::vec2 dims, float r, float g, float b)
	{
		float vertexData[] = {
			pos.x,			pos.y,			r, g, b, 1.0f, //TopLeft
			pos.x + dims.x, pos.y,			r, g, b, 1.0f, //TopRight
			pos.x + dims.x,	pos.y + dims.y, r, g, b, 1.0f, //BottomRight
			pos.x,			pos.y + dims.y, r, g, b, 1.0f, //BottomLeft
		};

		vertexBuffer->SetData(vertexData, sizeof(vertexData));

		renderAPI->Draw(vao.get());
	}

	void Renderer::destroy() {
		renderAPI->Shutdown();
	}
}
