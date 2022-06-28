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
		SLTH_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		SLTH_CORE_ASSERT(status, "Failed to initialize Glad!");

		SLTH_CORE_INFO("OpenGL Info:");
		SLTH_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		SLTH_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		SLTH_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

#ifdef SLTH_ENABLE_ASSERTS
		int versionMajor;
		int versionMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

		SLTH_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Sloth requires at least OpenGL version 4.5!");
#endif
	}

	void OpenGLContext::SwapBuffers()
	{
		SLTH_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}
}