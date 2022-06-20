#include "FrameBuffer.h"
#include "Platform/SDL/SdlFramebuffer.h"
#include "Platform/OpenGL/OpenGLFramebuffer.h"
#include "Sage/renderer/RenderAPI.h"

namespace Sage {
	std::unique_ptr<Framebuffer> Framebuffer::Create(int width, int height)
	{
		switch (RenderAPI::GetApi())
		{
		case API::OpenGL:
			return std::make_unique<OpenGLFramebuffer>(width, height);
		case API::SDL:
			return std::make_unique<SdlFramebuffer>(width, height);
		default:
			return nullptr;
		}
	}
}