#pragma once
#include "Sage/renderer/VertexArray.h"
#include <vector>

namespace Sage {
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		virtual void AddVertexBuffer(VertexBuffer* buffer) override;
		virtual void SetIndexBuffer(IndexBuffer* buffer) override;

		virtual const VertexBuffer* GetVertexBuffer(int index = 0) const override { return vertexBuffers[index]; };
		virtual VertexBuffer* GetVertexBuffer(int index = 0) override { return vertexBuffers[index]; };

		virtual const IndexBuffer* GetIndexBuffer() const override { return indexBuffer; };
		virtual IndexBuffer* GetIndexBuffer() override { return indexBuffer; };

		virtual void Bind() override;
		virtual void Unbind() override;
	private:
		uint32_t id;

		std::vector<VertexBuffer*> vertexBuffers;
		uint32_t attribIndex = 0;
		IndexBuffer* indexBuffer = nullptr;
	};
}