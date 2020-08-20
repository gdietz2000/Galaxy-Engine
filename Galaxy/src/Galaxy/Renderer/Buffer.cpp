#include "gxpch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Galaxy/Log.h"

#include "Platform/OpenGl/OpenGLBuffer.h"

namespace Galaxy
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None: GX_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
		case RendererAPI::OpenGL: return new OpenGLVertexBuffer(vertices, size);
		default:
			GX_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
	}
	
	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None: GX_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
		case RendererAPI::OpenGL: return new OpenGLIndexBuffer(indices, count);
		default:
			GX_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
	}
}