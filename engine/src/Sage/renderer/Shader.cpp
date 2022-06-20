#include "Shader.h"
#include "Sage/renderer/RenderAPI.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Sage {
	std::unique_ptr<Shader> Shader::Create(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
	{
		switch (RenderAPI::GetApi())	
		{
		case API::OpenGL:
			return std::make_unique<OpenGLShader>(vertexShaderSource, fragmentShaderSource);
		default:
			return nullptr;
		}
	}
}