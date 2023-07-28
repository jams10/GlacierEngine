#include "pch.h"
#include "Application.h"

namespace Glacier
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		GR_CORE_ASSERT(s_Instance == nullptr, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create()); // 윈도우 생성.
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (true)
		{
			if (m_Window->OnUpdate() == 0) break;
		}
	}

}