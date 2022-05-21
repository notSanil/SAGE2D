#include "FrameBuffer.h"
#include "Platform/SDL/SdlFramebuffer.h"


namespace Sage {
	std::unique_ptr<Framebuffer> Framebuffer::Create(int width, int height)
	{
		return std::make_unique<SdlFramebuffer>(width, height);
	}
}