#include <Sloth.h>
#include <Sloth/Core/EntryPoint.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "Sandbox2D.h"

#include "ExampleLayer.h"

class Sandbox : public Sloth::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{

	}

};

Sloth::Application* Sloth::CreateApplication()
{
	return new Sandbox();

}