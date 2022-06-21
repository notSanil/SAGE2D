#include "SdlBuffer.h"

namespace Sage {
	SdlVertexBuffer::SdlVertexBuffer(void* data, int vertexCount):
		data(data), numVertices(vertexCount)
	{
	}
	
	void SdlVertexBuffer::SetData(void* data, int vertexCount) 
	{
		this->data = data;
		numVertices = vertexCount;
	}

	void SdlVertexBuffer::SetLayout(const BufferLayout& layout) 
	{
		this->layout = layout;
	}

	BufferLayout& SdlVertexBuffer::GetLayout() 
	{
		return layout;
	}
}