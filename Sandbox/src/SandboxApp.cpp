#include <Glacier.h>

class ExampleLayer : public Glacier::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{

	}

	void OnUpdate() override
	{
	}

	void OnEvent(Glacier::Event& event) override
	{
		if (event.GetEventType() == Glacier::EventType::KeyPressed)
		{
			Glacier::KeyPressedEvent& e = (Glacier::KeyPressedEvent&)event;
			if (e.GetKeyCode() == GR_VK_TAB)
			{
				GR_TRACE("Tab key is pressed (event)!");
			}
		}
	}
};

class Sandbox : public Glacier::Application
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

Glacier::Application* Glacier::CreateApplication()
{
	return new Sandbox();
}
