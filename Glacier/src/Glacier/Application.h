#pragma once

#include "Core.h"

namespace Glacier
{
	class GLACIER_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		inline static Application& Get() { return *s_Instance; }
	private:
		bool m_IsRunning = true;

		static Application* s_Instance;
	};

	// Ŭ���̾�Ʈ �ʿ��� ���ǵǴ� �Լ�.
	Application* CreateApplication();
}