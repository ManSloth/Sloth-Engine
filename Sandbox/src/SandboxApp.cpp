#include <Sloth.h>

class ExampleLayer : public Sloth::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{

	}

	void OnUpdate() override
	{
		SLTH_INFO("ExampleLayer::Update");
	}

	void OnEvent(Sloth::Event& event) override
	{
		SLTH_TRACE("{0}", event);
	}
};

class Sandbox : public Sloth::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}

};

Sloth::Application* Sloth::CreateApplication()
{
	return new Sandbox();

}