#include "slthpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Sloth {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}