#include "gxpch.h"
#include "Framebuffer.h"

#include "Galaxy/Renderer/Renderer.h"

#include "Platform/OpenGl/OpenGLFrameBuffer.h"

namespace Galaxy
{
	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& specs)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: GX_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLFramebuffer>(specs);
		default:
			GX_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
	}
}