#pragma once
#include "Sage/renderer/Buffer.h"

namespace Sage {
	class SdlVertexBuffer : public VertexBuffer
	{
	public:
		SdlVertexBuffer() = default;
		SdlVertexBuffer(void* data, int vertexCount);

		virtual void SetData(void* data, int vertexCount) override;

		virtual void SetLayout(const BufferLayout& layout) override;
		virtual BufferLayout& GetLayout() override;
	private:
		void* data;
		BufferLayout layout;
		int numVertices;
	};
}