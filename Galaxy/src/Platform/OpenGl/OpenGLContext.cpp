#include "gxpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Galaxy
{
	OpenGLContext::OpenGLContext(GLFWwindow* window)
		: m_WindowHandle(window)
	{
		GX_CORE_ASSERT(m_WindowHandle, "Window Handle is null!!!");
	}

	void OpenGLContext::Init()
	{
		GX_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		GX_CORE_ASSERT(status, "Failed to initialized Glad!");

		GX_CORE_INFO("OpenGL Info:");
		GX_CORE_INFO("	Vendor: {0}", glGetString(GL_VENDOR));
		GX_CORE_INFO("	Renderer: {0}", glGetString(GL_RENDERER));
		GX_CORE_INFO("	Version: {0}", glGetString(GL_VERSION));

	}

	void OpenGLContext::SwapBuffers()
	{
		GX_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}
}