#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Sage/Core/Log.h"

namespace Sage {
	enum class DataType
	{
		None = 0,
		Float, Float2, Float3, Float4,
		Int, Int2, Int3, Int4,
		Bool,
	};

	static uint32_t GetElementSize(DataType type)
	{
		switch (type)
		{
		case Sage::DataType::None:
			return 0;
		case Sage::DataType::Float:
			return 4;
		case Sage::DataType::Float2:
			return 4 * 2;
		case Sage::DataType::Float3:
			return 4 * 3;
		case Sage::DataType::Float4:
			return 4 * 4;
		case Sage::DataType::Int:
			return 4;
		case Sage::DataType::Int2:
			return 4 * 2;
		case Sage::DataType::Int3:
			return 4 * 3;
		case Sage::DataType::Int4:
			return 4 * 4;
		case Sage::DataType::Bool:
			return 1;
		default:
			SAGE_CORE_CRIT("Unknown data type, size not known");
			return 0;
		}
	}

	struct BufferElement
	{
		std::string Name;
		DataType Type = DataType::None;
		uint32_t Offset = 0;

		uint32_t GetElementCount()
		{
			switch (Type)
			{
			case Sage::DataType::None:		return 0;
			case Sage::DataType::Float:		return 1;
			case Sage::DataType::Float2:	return 2;
			case Sage::DataType::Float3:	return 3;
			case Sage::DataType::Float4:	return 4;
			case Sage::DataType::Int:		return 1;
			case Sage::DataType::Int2:		return 2;
			case Sage::DataType::Int3:		return 3;
			case Sage::DataType::Int4:		return 4;
			case Sage::DataType::Bool:		return 1;
			}
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout() = default;
		BufferLayout(std::initializer_list<BufferElement> elems) :
			elements(elems)
		{
			CalculateStrideAndOffset();
		}

		uint32_t GetStride()
		{
			return stride;
		}

		size_t GetSize() { return elements.size(); }

		std::vector<BufferElement>::iterator begin() { return elements.begin(); }
		std::vector<BufferElement>::iterator end() { return elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return elements.end(); }

		BufferElement& operator[] (size_t index)
		{
			return elements[index];
		}
	private:
		void CalculateStrideAndOffset()
		{
			uint32_t offset = 0;
			for (auto& element : elements)
			{
				element.Offset = offset;
				offset += GetElementSize(element.Type);
			}
			stride = offset;
		}

	private:
		std::vector<BufferElement> elements;
		uint32_t stride = 0;
	};

	//This class assumes no ownership of the data
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void SetData(void* data, int size) = 0;

		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual BufferLayout& GetLayout() = 0;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		static std::unique_ptr<VertexBuffer> Create(int size);
		static std::unique_ptr<VertexBuffer> Create(void* data, int size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual int GetCount() = 0;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		static std::unique_ptr<IndexBuffer> Create(uint32_t* indices, int indexCount);
	};
}
