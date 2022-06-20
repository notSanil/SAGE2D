#include "RenderAPI.h"
#include "Sage/Core/Log.h"
#include "Platform/OpenGL/OpenGLRenderAPI.h"

namespace Sage {
	std::unique_ptr<RenderAPI> RenderAPI::Create()
	{
		switch (currentApi)
		{
		case API::OpenGL:
			return std::make_unique<OpenGLRenderAPI>();
		case API::SDL:
			return nullptr;
		default:
			SAGE_CORE_CRIT("No API selected");
			return nullptr;
		}
	}

	API RenderAPI::currentApi = API::OpenGL;
}
