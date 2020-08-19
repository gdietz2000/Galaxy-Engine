#pragma once

#include "Galaxy/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Galaxy
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* window);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}