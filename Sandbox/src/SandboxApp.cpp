#include <Glacier.h>

class ExampleLayer : public Glacier::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{

	}

	void OnUpdate() override
	{
		//std::pair<float, float> pos = Glacier::Input::GetMousePosition();
		//GR_TRACE("{0}/{1}", pos.first, pos.second);
	}

	void OnEvent(Glacier::Event& event) override
	{
		GR_TRACE({ "0" }, event);
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
