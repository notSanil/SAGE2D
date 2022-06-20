#pragma once
#include "Sage/renderer/Shader.h"


namespace Sage {
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
		~OpenGLShader();

		virtual void Bind() override;
		virtual void Unbind() override;

	private:
		uint32_t id;
	};
}