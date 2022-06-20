#include "OpenGLRenderer.h"


namespace Sage {
	void OpenGLRenderer::init(Sage::Window* window)
	{
		float vertices[] = {
			-1.0f, -1.0f,
			1.0f, -1.0f,
			0.0f, 0.0f
		};

		uint32_t VBO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_VERTEX_ARRAY, VBO);
		glBufferData(GL_VERTEX_ARRAY, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	}

	void OpenGLRenderer::destroy()
	{
	}


	void OpenGLRenderer::StartScene()
	{
		glClearColor(0.5, 0.0, 0.5, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLRenderer::EndScene()
	{
	}

	void OpenGLRenderer::RenderTexture(Sage::Texture* texture, glm::ivec2 pos, glm::ivec2 dims, glm::ivec4 color)
	{
	}
	void OpenGLRenderer::RenderTexture(Sage::Texture* texture, glm::ivec4 texSize, glm::ivec4 destSize, glm::ivec4 color)
	{

	}
	void OpenGLRenderer::RenderTexture(Sage::Texture* texture, glm::ivec4 texSize, glm::imat3x2& transform, glm::ivec4 color)
	{

	}
	void OpenGLRenderer::RenderRotatedTexture(Sage::Texture* texture, glm::ivec4 texSize, glm::imat3x2& transform, glm::ivec4 color)
	{

	}
	void OpenGLRenderer::RenderRect(glm::ivec2 pos, glm::ivec2 dims, int r, int g, int b)
	{
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
}