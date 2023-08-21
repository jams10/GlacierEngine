#include "pch.h"
#include "Application.h"

#include "Glacier/Renderer/Renderer.h"
#include "Glacier/Window/Window.h"

namespace Glacier
{

	Application* Application::s_Instance = nullptr;

	Application::Application(std::wstring appName)
	{
		GR_CORE_ASSERT(s_Instance == nullptr, "Application already exists!");
		s_Instance = this;

		// ������ �޽��� �߻� �� �̺�Ʈ�� ����� �Ѱ��� �� ó������ �ݹ� �Լ��� ���ڷ� ���� �Ѱ� ������ ����.
		// ������ ���� �Ŀ� �ݹ� �Լ��� ���ε� ������, ������ ���� �� WM_SIZE �޽����� �ٷ� �߻��ϰ� �Ǵµ� 
		// �� ���������� �ݹ� �Լ��� ���ε� �Ǿ� ���� �ʱ� ������ �� �Լ� ��ü�� ȣ���ϱ� ������ bad_function_call ���� �߻�.
		// ����, ������ Ŭ���� ��ü ���� ������ �ݹ� �Լ��� ���� ���ε� ����.
		m_Window = std::unique_ptr<Window>(Window::Create(BIND_EVENT_CALLBACK(&Application::ProcessEvent)));
		m_Window->SetTitle(appName);

		m_ImGuiLayer = new ImGuiLayer(); // ImGuiLayer ����.
		PushOverlay(m_ImGuiLayer);       // ImGuiLayer�� Overlay ���̾ �߰�.
	}

	Application::~Application()
	{
		// entry point �ν��Ͻ� ���� ���ŵ�.
		s_Instance = nullptr;
	}

	void Application::Run()
	{
		while (m_IsRunning)
		{
			m_GameTimer.Tick();

			Renderer::ResetStat();

			if (!m_Minimized)
			{
				for (Layer* layer : m_LayerStack) // ���̾���� update ȣ��.
					layer->OnUpdate(m_GameTimer.GetDeltaTime());
			}

			// ImGui GUI�� �׷���.
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			// swap buffer
			m_Window->OnUpdate();
		}
	}

	void Application::Close()
	{
		m_IsRunning = false;
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}

	void Application::ProcessEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		// ���� �̺�Ʈ�� WindowCloseEvent�� ���, OnWindowClose �Լ��� ȣ���ϵ��� ��.
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_CALLBACK(&Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_CALLBACK(&Application::OnWindowResize));

		// ���� ���̾���� �̺�Ʈ�� �޵��� ��. �̺�Ʈ�� ���� ���̾ ���� ���̾�� �̺�Ʈ�� �������� �ʱ� ���� Handled ���� true�� �ٲٸ� 
		// �ش� �̺�Ʈ�� �� �̻� ó������ �ʰ� ��������.
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(event);
			if (event.Handled)
				break;
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent event)
	{
		m_IsRunning = false;
		return true; // ���� ���̾ �̺�Ʈ�� �������� �ʵ��� true ����.
	}

	bool Application::OnWindowResize(WindowResizeEvent event)
	{
		if (event.GetWidth() == 0 || event.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(event.GetWidth(), event.GetHeight());

		return false;
	}
}