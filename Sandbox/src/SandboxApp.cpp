#include <Sloth.h>

class Sandbox : public Sloth::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}

};

Sloth::Application* Sloth::CreateApplication()
{
	return new Sandbox();

}