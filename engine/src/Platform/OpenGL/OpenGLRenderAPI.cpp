#include "OpenGLRenderAPI.h"
#include <glad/glad.h>
#include "Sage/Core/Log.h"
#include <glm/gtc/type_ptr.hpp>
namespace Sage {
	void OpenGLMessageCallback(
		unsigned source,
		unsigned type,
		unsigned id,
		unsigned severity,
		int length,
		const char* message,
		const void* userParam)
	{
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:         SAGE_CORE_CRIT(message); return;
		case GL_DEBUG_SEVERITY_MEDIUM:       SAGE_CORE_ERROR(message); return;
		case GL_DEBUG_SEVERITY_LOW:          SAGE_CORE_WARN(message); return;
		case GL_DEBUG_SEVERITY_NOTIFICATION: SAGE_CORE_TRACE(message); return;
		}
	}

	void OpenGLRenderAPI::Init(Window* window)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(OpenGLMessageCallback, nullptr);

		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
	}

	void OpenGLRenderAPI::Shutdown()
	{

	}

	void OpenGLRenderAPI::SetViewport(int x, int y, int width, int height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRenderAPI::SetClearColor(glm::vec4 color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}
	
	void OpenGLRenderAPI::ClearScreen()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRenderAPI::Draw(VertexArray* vertexArray)
	{
		vertexArray->Bind();
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
		vertexArray->Unbind();
	}

	void OpenGLRenderAPI::SetUniformMat4(uint32_t location, glm::mat4& matrix)
	{
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}