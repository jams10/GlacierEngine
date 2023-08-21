#include <Glacier.h>
#include <Glacier/Core/EntryPoint.h> // ���⼭�� �������� include ���־�� main �Լ��� �ߺ����� ����.

#include "SandBox3D.h"

namespace Glacier
{
	class Sandbox : public Glacier::Application
	{
	public:
		Sandbox() : Application(L"Sandbox")
		{
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
}

