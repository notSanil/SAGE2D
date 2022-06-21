#include "VertexArray.h"
#include "Sage/renderer/RenderAPI.h"
#include "Sage/Core/Log.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Sage {
	std::unique_ptr<VertexArray> VertexArray::Create()
	{
		switch (RenderAPI::GetApi())
		{
		case API::OpenGL:
			return std::make_unique<OpenGLVertexArray>();
		default:
			SAGE_CORE_CRIT("No RenderAPI selected");
			return nullptr;
		}
	}
}