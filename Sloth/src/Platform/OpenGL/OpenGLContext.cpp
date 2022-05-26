#include "slthpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Sloth 
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		SLTH_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		SLTH_CORE_ASSERT(status, "Failed to initialize Glad!");

		SLTH_CORE_INFO("OpenGL Info:");
		SLTH_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		SLTH_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		SLTH_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}