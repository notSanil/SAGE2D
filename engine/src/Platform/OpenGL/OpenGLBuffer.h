#pragma once
#include "Sage/renderer/Buffer.h"

namespace Sage {
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(int size);
		OpenGLVertexBuffer(void* data, int size);
		~OpenGLVertexBuffer();

		virtual void SetData(void* data, int size) override;

		virtual void SetLayout(const BufferLayout& layout) override { this->layout = layout; };
		virtual BufferLayout& GetLayout() override { return layout; };

		virtual void Bind() override;
		virtual void Unbind() override;

	private:
		unsigned int id;
		BufferLayout layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* data, int indexCount);
		~OpenGLIndexBuffer();

		virtual int GetCount() override { return count; };

		virtual void Bind() override;
		virtual void Unbind() override;

	private:
		unsigned int id;
		int count = 0;
	};
}