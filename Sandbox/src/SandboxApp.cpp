#include <Glacier.h>
#include <Glacier/Core/EntryPoint.h> // ���⼭�� �������� include ���־�� main �Լ��� �ߺ����� ����.

#include "SandBox3D.h"

class ExampleLayer : public Glacier::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{
	}

	void OnUpdate(float dt) override
	{
	}

	void OnEvent(Glacier::Event& event) override
	{	
	}

private:
};

class Sandbox : public Glacier::Application
{
public:
	Sandbox()
	{
		// PushLayer(new ExampleLayer());
		PushLayer(new SandBox3D());
	}

	~Sandbox()
	{

	}
};

Glacier::Application* Glacier::CreateApplication()
{
	return new Sandbox();
}
