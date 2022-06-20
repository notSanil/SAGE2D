#include "OpenGLVertexArray.h"
#include "glad/glad.h"
#include "Sage/Core/Log.h"

namespace Sage {
	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &id);
	}
	
	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &id);
	}

	void OpenGLVertexArray::AddVertexBuffer(VertexBuffer* buffer)
	{
		if (buffer->GetLayout().GetSize() == 0)
		{
			SAGE_CORE_ERROR("Vertex Buffer Layout not set");
		}

		Bind();
		buffer->Bind();
		for (auto& element : buffer->GetLayout())
		{
			switch (element.Type)
			{
			case DataType::Float:
			case DataType::Float2:
			case DataType::Float3:
			case DataType::Float4:
			{
				glEnableVertexAttribArray(attribIndex);
				glVertexAttribPointer(attribIndex, element.GetElementCount(), GL_FLOAT, 
					GL_FALSE, buffer->GetLayout().GetStride(), (const void*)element.Offset);
				++attribIndex;
				break;
			}
			case DataType::Int:
			case DataType::Int2:
			case DataType::Int3: 
			case DataType::Int4:
			{
				glEnableVertexAttribArray(attribIndex);
				glVertexAttribIPointer(attribIndex, element.GetElementCount(), GL_INT, 
					buffer->GetLayout().GetStride(), (const void*)element.Offset);
				++attribIndex;
				break;
			}
			case DataType::Bool:
			{
				glEnableVertexAttribArray(attribIndex);
				glVertexAttribIPointer(attribIndex, element.GetElementCount(), GL_BOOL,
					buffer->GetLayout().GetStride(), (const void*)element.Offset);
				++attribIndex;
				break;
			}
			default:
				break;
			}
		}
		Unbind();
		buffer->Unbind();

		vertexBuffers.push_back(buffer);
	}
	
	void OpenGLVertexArray::SetIndexBuffer(IndexBuffer* buffer)
	{
		Bind();
		buffer->Bind();

		Unbind();
		buffer->Unbind();

		indexBuffer = buffer;
	}

	void OpenGLVertexArray::Bind()
	{
		glBindVertexArray(id);
	}

	void OpenGLVertexArray::Unbind()
	{
		glBindVertexArray(0);
	}
}