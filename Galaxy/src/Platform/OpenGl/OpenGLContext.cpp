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
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		GX_CORE_ASSERT(status, "Failed to initialized Glad!");
	}

	void OpenGLContext::SwapBuffers()
	{
		glBegin(GL_TRIANGLES);

		glEnd();
		glfwSwapBuffers(m_WindowHandle);
	}
}