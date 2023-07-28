#pragma once

#include "Core.h"
#include "Window/Window.h"

namespace Glacier
{
	class GLACIER_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
	private:
		std::unique_ptr<Window> m_Window;
		bool m_IsRunning = true;

		static Application* s_Instance;
	};

	// 클라이언트 쪽에서 정의되는 함수.
	Application* CreateApplication();
}