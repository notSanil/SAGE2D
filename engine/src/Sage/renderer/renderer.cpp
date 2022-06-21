#include "renderer.hpp"

#include "Sage/Core/Log.h"
#include <glm/gtx/matrix_transform_2d.hpp>

namespace Sage {
	std::unique_ptr<RenderAPI> Renderer::renderAPI;
	std::unique_ptr<VertexArray> Renderer::vao;
	std::unique_ptr<VertexBuffer> Renderer::vertexBuffer;
	std::unique_ptr<IndexBuffer> Renderer::indexBuffer;
	std::unique_ptr<Shader> Renderer::shader;

	static glm::vec3 quadPositions[4];
	static glm::vec3 texCoords[4];
	struct Vertex
	{
		glm::vec2 pos;
		glm::vec4 color;
		glm::vec2 texCoords;
	};

	void Renderer::init(Window* window)
	{
		renderAPI = RenderAPI::Create();
		renderAPI->Init(window);
		renderAPI->SetClearColor({ 0, 0, 0, 1 });
		renderAPI->SetViewport(0, 0, window->GetWidth(), window->GetHeight());

		vao = VertexArray::Create();

		vertexBuffer = VertexBuffer::Create(4 * sizeof(Vertex));
		vertexBuffer->SetLayout({ 
			{"pos", DataType::Float2},
			{"color", DataType::Float4},
			{"textureCoord", DataType::Float2}
		});
		vao->AddVertexBuffer(vertexBuffer.get());

		uint32_t indices[] = { 0, 1, 2, 
								2, 3, 0 };
		indexBuffer = IndexBuffer::Create(indices, 6);
		vao->SetIndexBuffer(indexBuffer.get());

		shader = Shader::Create("resources/shaders/VertexShader.glsl", "resources/shaders/FragShader.glsl");

		quadPositions[0] = {-0.5f,  0.5f, 1.0f }; 
		quadPositions[1] = { 0.5f,  0.5f, 1.0f };
		quadPositions[2] = { 0.5f, -0.5f, 1.0f };
		quadPositions[3] = {-0.5f, -0.5f, 1.0f };

		texCoords[0] = {0.0f, 1.0f, 1.0f};
		texCoords[1] = {1.0f, 1.0f, 1.0f};
		texCoords[2] = {1.0f, 0.0f, 1.0f};
		texCoords[3] = {0.0f, 0.0f, 1.0f};
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

	void Renderer::RenderTexture(Texture* texture, const glm::vec2& pos, const glm::vec2& dims, const glm::vec4& color)
	{
		glm::mat3 transform = glm::translate(glm::mat3(1.0f), pos) * glm::scale(glm::mat3(1.0f), dims);		
		RenderTexture(texture, glm::mat3(1.0f), transform, color);
	}

	void Renderer::RenderTexture(Texture* texture, const glm::vec4& texSize, const glm::vec4& destSize, const glm::vec4& color)
	{
		glm::mat3 transform = glm::translate(glm::mat3(1.0f), { destSize.x, destSize.y }) * 
			glm::scale(glm::mat3(1.0f), { destSize.z, destSize.w });
		RenderTexture(texture, texSize, transform, color);
	}

	void Renderer::RenderTexture(Texture* texture, const glm::vec4& texSize, const glm::mat3& transform, const glm::vec4& color)
	{
		glm::mat3 textureTransform = glm::translate(glm::mat3(1.0f), { texSize.x, texSize.y }) *
			glm::scale(glm::mat3(1.0f), { texSize.z, texSize.w });
		RenderTexture(texture, textureTransform, transform, color);
	}

	void Renderer::RenderRotatedTexture(Texture* texture, const glm::vec4& texSize, const glm::mat3& transform, const glm::vec4& color)
	{
		glm::mat3 textureTransform = glm::translate(glm::mat3(1.0f), { texSize.x, texSize.y }) *
			glm::scale(glm::mat3(1.0f), { texSize.z, texSize.w });
		RenderTexture(texture, textureTransform, transform, color);
	}

	void Renderer::RenderTexture(Texture* texture, const glm::mat3& textureTransform, const glm::mat3& transform, const glm::vec4& color)
	{
		Vertex vertices[4];
		for (int i = 0; i < 4; ++i)
		{
			vertices[i].pos = transform * quadPositions[i];
			vertices[i].color = color;
			vertices[i].texCoords = textureTransform * texCoords[i];
		}
		vertexBuffer->SetData(vertices, sizeof(vertices));
		texture->Bind();
		renderAPI->Draw(vao.get());
		texture->Unbind();
	}

	void Renderer::RenderRect(const glm::vec2& pos, const glm::vec2& dims, const glm::vec4& color)
	{
		Vertex vertices[4];

		glm::mat3 transform = glm::translate(glm::mat3(1.0f), pos) * glm::scale(glm::mat3(1.0f), dims);
		for (int i = 0; i < 4; ++i)
		{
			vertices[i].pos = transform * quadPositions[i];
			vertices[i].color = color;
			vertices[i].texCoords = texCoords[i];
		}
		vertexBuffer->SetData(vertices, sizeof(vertices));
		TextureManager::loadWhiteTexture()->Bind();
		renderAPI->Draw(vao.get());
	}

	void Renderer::destroy() {
		renderAPI->Shutdown();
	}
}
