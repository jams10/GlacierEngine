#include <Glacier.h>
#include <Glacier/Core/EntryPoint.h> // 여기서만 진입점을 include 해주어야 main 함수가 중복되지 않음.

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

