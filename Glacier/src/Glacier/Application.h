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

	// 클라이언트 쪽에서 정의되는 함수.
	Application* CreateApplication();
}