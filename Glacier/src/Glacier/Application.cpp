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

		// 윈도우 메시지 발생 시 이벤트를 만들어 넘겼을 때 처리해줄 콜백 함수를 인자로 같이 넘겨 윈도우 생성.
		// 원래는 생성 후에 콜백 함수를 바인딩 했으나, 윈도우 생성 시 WM_SIZE 메시지가 바로 발생하게 되는데 
		// 이 시점에서는 콜백 함수가 바인딩 되어 있지 않기 때문에 빈 함수 객체를 호출하기 때문에 bad_function_call 오류 발생.
		// 따라서, 윈도우 클래스 객체 생성 시점에 콜백 함수도 같이 바인딩 해줌.
		m_Window = std::unique_ptr<Window>(Window::Create(BIND_EVENT_CALLBACK(&Application::ProcessEvent)));
		m_Window->SetTitle(appName);

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
		while (m_IsRunning)
		{
			m_GameTimer.Tick();

			Renderer::ResetStat();

			if (!m_Minimized)
			{
				for (Layer* layer : m_LayerStack) // 레이어들의 update 호출.
					layer->OnUpdate(m_GameTimer.GetDeltaTime());
			}

			// ImGui GUI를 그려줌.
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
		// 들어온 이벤트가 WindowCloseEvent인 경우, OnWindowClose 함수를 호출하도록 함.
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_CALLBACK(&Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_CALLBACK(&Application::OnWindowResize));

		// 상위 레이어부터 이벤트를 받도록 함. 이벤트를 받은 레이어가 하위 레이어로 이벤트를 전파하지 않기 위해 Handled 값을 true로 바꾸면 
		// 해당 이벤트를 더 이상 처리하지 않고 빠져나감.
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
		return true; // 하위 레이어에 이벤트를 전파하지 않도록 true 리턴.
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