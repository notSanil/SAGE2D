#include "OpenGLShader.h"
#include "Sage/Core/Log.h"
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <vector>

namespace Sage {
	OpenGLShader::OpenGLShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
	{
		std::stringstream buffer;

		std::ifstream vertexShaderFile(vertexShaderPath);
		buffer << vertexShaderFile.rdbuf();
		std::string vertexShaderData = buffer.str();
		const GLchar* vertexShaderSource = (const GLchar*)vertexShaderData.c_str();

		uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, 0);
		glCompileShader(vertexShader);
		
		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<char> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			// Use the infoLog as you see fit.
			SAGE_CORE_CRIT("Vertex Shader Compilation failed. {0}", infoLog.data());

			// In this simple program, we'll just leave
			return;
		}
		buffer.str("");

		std::ifstream fragmentShaderFile(fragmentShaderPath);
		buffer << fragmentShaderFile.rdbuf();
		std::string fragmentShaderData = buffer.str();
		const GLchar* fragmentShaderSource = (const GLchar*)fragmentShaderData.c_str();

		uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, 0);
		glCompileShader(fragmentShader);

		isCompiled = 0;
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<char> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);

			// Use the infoLog as you see fit.
			SAGE_CORE_CRIT("Fragment Shader Compilation failed. {0}", infoLog.data());

			// In this simple program, we'll just leave
			return;
		}

		id = glCreateProgram();
		glAttachShader(id, vertexShader);
		glAttachShader(id, fragmentShader);

		glLinkProgram(id);

		GLint isLinked = 0;
		glGetProgramiv(id, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(id, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<char> infoLog(maxLength);
			glGetProgramInfoLog(id, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(id);
			id = 0;
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			// Use the infoLog as you see fit.
			SAGE_CORE_CRIT("Program linking failed. {0}", infoLog.data());
			// In this simple program, we'll just leave
			return;
		}

		glDetachShader(id, vertexShader);
		glDetachShader(id, fragmentShader);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(id);
	}

	void OpenGLShader::Bind()
	{
		glUseProgram(id);
	}

	void OpenGLShader::Unbind()
	{
		glUseProgram(0);
	}
}