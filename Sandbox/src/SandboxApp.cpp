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
		//SLTH_INFO("ExampleLayer::Update");

		if (Sloth::Input::IsKeyPressed(SLTH_KEY_TAB))  // Poll tab key
			SLTH_TRACE("Tab key is pressed!");
	}

	void OnEvent(Sloth::Event& event) override
	{
		if (event.GetEventType() == Sloth::EventType::KeyPressed)
		{
			Sloth::KeyPressedEvent& e = (Sloth::KeyPressedEvent&)event; // print key that is pressed
			SLTH_TRACE("{0}", (char)e.GetKeyCode());
		}

		//SLTH_TRACE("{0}", event);
	}
};

class Sandbox : public Sloth::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushLayer(new Sloth::ImGuiLayer());
	}

	~Sandbox()
	{

	}

};

Sloth::Application* Sloth::CreateApplication()
{
	return new Sandbox();

}