#include "slthpch.h"
#include "Application.h"

#include "Sloth/Events/ApplicationEvent.h"
#include "Sloth/Log.h"

namespace Sloth {

	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		SLTH_TRACE(e);

		while (true);
	}

}