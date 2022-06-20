#pragma once
#include <string>
#include <memory>

namespace Sage {
	class Shader
	{
	public:
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		static std::unique_ptr<Shader> Create(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
	};
}