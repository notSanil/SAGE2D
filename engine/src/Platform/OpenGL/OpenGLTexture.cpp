#include "OpenGLTexture.h"
#include <glad/glad.h>
#include <stb_image.h>
#include "Sage/Core/Log.h"

namespace Sage {

	static GLint ConvertResizingPolicy(ResizingPolicy policy)
	{
		switch (policy)
		{
		case ResizingPolicy::Linear:
			return GL_LINEAR;
		case ResizingPolicy::Nearest:
			return GL_NEAREST;
		default:
			return GL_NONE;
		}
	}
	OpenGLTexture::OpenGLTexture(uint32_t width, uint32_t height)
		:width(width), height(height)
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &id);
		glTextureStorage2D(id, 1, GL_RGBA8, width, height);

		glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureParameteri(id, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(id, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	OpenGLTexture::OpenGLTexture(uint32_t width, uint32_t height, AccessFormat format)
		:width(width), height(height)
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &id);
		glTextureStorage2D(id, 1, GL_RGBA8, width, height);

		glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureParameteri(id, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(id, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	OpenGLTexture::OpenGLTexture(const std::string& path)
	{
		int w, h;
		int noOfChannels;
		void* data = stbi_load(path.c_str(), &w, &h, &noOfChannels, STBI_rgb_alpha);
		//stbi_set_flip_vertically_on_load(1);
		if (data == nullptr)
		{
			SAGE_CORE_ERROR("Failed to load texture. {0}", path);
		}
		width = w;
		height = h;

		glCreateTextures(GL_TEXTURE_2D, 1, &id);
		glTextureStorage2D(id, 1, GL_RGBA8, w, h);

		glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureParameteri(id, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(id, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(id, 0, 0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);
	}

	OpenGLTexture::OpenGLTexture(const std::string& path, ResizingPolicy resizingPolicy)
	{
		int w, h;
		int noOfChannels;
		void* data = stbi_load(path.c_str(), &w, &h, &noOfChannels, STBI_rgb_alpha);
		//stbi_set_flip_vertically_on_load(1);
		if (data == nullptr)
		{
			SAGE_CORE_ERROR("Failed to load texture. {0}", path);
		}
		width = w;
		height = h;

		glCreateTextures(GL_TEXTURE_2D, 1, &id);
		glTextureStorage2D(id, 1, GL_RGBA8, w, h);

		glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, ConvertResizingPolicy(resizingPolicy));
		glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, ConvertResizingPolicy(resizingPolicy));

		glTextureParameteri(id, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(id, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(id, 0, 0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);
	}

	OpenGLTexture::~OpenGLTexture()
	{
		glDeleteTextures(1, &id);
	}

	void OpenGLTexture::Bind()
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, id);
	}
	
	void OpenGLTexture::Unbind()
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void OpenGLTexture::setData(void* data)
	{
		glTextureSubImage2D(id, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
}