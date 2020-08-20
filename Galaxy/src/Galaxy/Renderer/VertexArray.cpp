#include "gxpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGl/OpenGLVertexArray.h"

namespace Galaxy
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: GX_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
		default:
			GX_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
	}
}