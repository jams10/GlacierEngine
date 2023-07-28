#include <Glacier.h>

class Sandbox : public Glacier::Application
{
public:
	Sandbox()
	{
		
	}

	~Sandbox()
	{

	}
};

Glacier::Application* Glacier::CreateApplication()
{
	return new Sandbox();
}
