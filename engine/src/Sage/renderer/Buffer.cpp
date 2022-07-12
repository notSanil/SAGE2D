#include "Buffer.h"
#include "Sage/renderer/RenderAPI.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Sage {
	std::unique_ptr<VertexBuffer> VertexBuffer::Create(int size)
	{
		switch (RenderAPI::GetApi())
		{
		case API::None:
			return nullptr;
		case API::OpenGL:
			return std::make_unique<OpenGLVertexBuffer>(size);
		default:
			return nullptr;
		}
	}
	
	std::unique_ptr<VertexBuffer> VertexBuffer::Create(void* data, int size)
	{
		switch (RenderAPI::GetApi())
		{
		case API::None:
			return nullptr;
		case API::OpenGL:
			return std::make_unique<OpenGLVertexBuffer>(data, size);
		default:
			return nullptr;
		}
	}
	


	//////////////////////////IndexBuffer//////////////////
	std::unique_ptr<IndexBuffer> IndexBuffer::Create(uint32_t* indices, int indexCount)
	{
		switch (RenderAPI::GetApi())
		{
		case API::None:
			return nullptr;
		case API::OpenGL:
			return std::make_unique<OpenGLIndexBuffer>(indices, indexCount);
		default:
			return nullptr;
		}
	}
}
