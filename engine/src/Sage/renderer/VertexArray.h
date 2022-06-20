#pragma once
#include <memory>
#include "Sage/renderer/Buffer.h"

namespace Sage{
	class VertexArray
	{
	public:
		virtual ~VertexArray() = default;

		virtual void AddVertexBuffer(VertexBuffer* buffer) = 0;
		virtual void SetIndexBuffer(IndexBuffer* buffer) = 0;

		virtual const VertexBuffer* GetVertexBuffer(int index = 0) const = 0;
		virtual VertexBuffer* GetVertexBuffer(int index = 0) = 0;
		
		virtual const IndexBuffer* GetIndexBuffer() const = 0;
		virtual IndexBuffer* GetIndexBuffer() = 0;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		static std::unique_ptr<VertexArray> Create();
	};
}