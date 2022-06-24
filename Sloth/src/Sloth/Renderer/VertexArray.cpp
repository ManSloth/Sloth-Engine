#include "slthpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Sloth {

	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		SLTH_CORE_ASSERT(false, "RenderAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:	return std::make_shared<OpenGLVertexArray>();
		}

		SLTH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
