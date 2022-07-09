#include <Sloth.h>
#include <Sloth/Core/EntryPoint.h>

//#include "Platform/OpenGL/OpenGLShader.h"

#include "EditorLayer.h"


namespace Sloth {

	class SlothEditor : public Application
	{
	public:
		SlothEditor()
			: Application("Sloth Editor - [Untitled]* ")
		{
			//PushLayer(new ExampleLayer());
			PushLayer(new EditorLayer());
		}

		~SlothEditor()
		{

		}

	};

	Application* CreateApplication()
	{
		return new SlothEditor();

	}
}