#include "gxpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGl/OpenGLRendererAPI.h"

namespace Galaxy
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}