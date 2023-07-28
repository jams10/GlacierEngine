#include "pch.h"
#include "Application.h"

#include "Platform/DirectX/DirectX11Context.h"

namespace Glacier
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		GR_CORE_ASSERT(s_Instance == nullptr, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create()); // 윈도우 생성.
		m_Context = std::unique_ptr<GraphicsContext>(new DirectX11Context(m_Window->GetNativeWindow()));
		m_Context->Init();

		m_ImGuiLayer = new ImGuiLayer(); // ImGuiLayer 생성.
		PushOverlay(m_ImGuiLayer);       // ImGuiLayer를 Overlay 레이어에 추가.
	}

	Application::~Application()
	{
		// entry point 인스턴스 에서 제거됨.
		s_Instance = nullptr;
	}

	void Application::Run()
	{
		while (true)
		{
			if (m_Window->OnUpdate() == 0) break;

			for (Layer* layer : m_LayerStack) // 레이어들의 update 호출.
				layer->OnUpdate();

			// ImGui GUI를 그려줌.
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Context->SwapBuffers();
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}

}