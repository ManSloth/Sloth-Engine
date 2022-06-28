#include "slthpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Sloth {

	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}