#include <Sloth.h>
#include <Sloth/Core/EntryPoint.h>

//#include "Platform/OpenGL/OpenGLShader.h"

#include "EditorLayer.h"


namespace Sloth {

	class SlothEditor : public Application
	{
	public:
		SlothEditor(ApplicationCommandLineArgs args)
			: Application("Sloth-Editor", args)
		{
			PushLayer(new EditorLayer());
		}

		~SlothEditor()
		{

		}

	};

	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		return new SlothEditor(args);

	}
}