#include "pch.h"
#include "Application.h"

#include "Platform/DirectX/DirectX11System.h"

namespace Glacier
{

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		GR_CORE_ASSERT(s_Instance == nullptr, "Application already exists!");
		s_Instance = this;

		// 윈도우 메시지 발생 시 이벤트를 만들어 넘겼을 때 처리해줄 콜백 함수를 인자로 같이 넘겨 윈도우 생성.
		// 원래는 생성 후에 콜백 함수를 바인딩 했으나, 윈도우 생성 시 WM_SIZE 메시지가 바로 발생하게 되는데 
		// 이 시점에서는 콜백 함수가 바인딩 되어 있지 않기 때문에 빈 함수 객체를 호출하기 때문에 bad_function_call 오류 발생.
		// 따라서, 윈도우 클래스 객체 생성 시점에 콜백 함수도 같이 바인딩 해줌.
		m_Window = std::unique_ptr<Window>(Window::Create(BIND_EVENT_CALLBACK(&Application::ProcessEvent));			

		m_ImGuiLayer = new ImGuiLayer(); // ImGuiLayer 생성.
		PushOverlay(m_ImGuiLayer);       // ImGuiLayer를 Overlay 레이어에 추가.

		/*
		*	임시 테스트 도형 그리기.
		*/
		//  정점 버퍼 생성.
		//  인덱스 버퍼 생성.
		//  쉐이더 생성.
		//  인풋 레이아웃 생성.

		float vertices[3 * 6] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
			 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
		};
		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		BufferLayout layout = {
			{ ShaderDataType::Float3, "Position" },
			{ ShaderDataType::Float3, "Color" }
		};
		m_VertexBuffer->SetLayout(layout);

		uint32 indices[3] = { 0,1,2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32)));

		m_VertexShader.reset(VertexShader::Create(L"../Glacier/resources/shaders/VertexColorVS.hlsl"));
		m_FragmentShader.reset(FragmentShader::Create(L"../Glacier/resources/shaders/VertexColorPS.hlsl"));

		m_InputLayout.reset(VertexLayout::Create(m_VertexShader.get()));
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
			// begin frame
			DirectX11System::GetInstance()->BeginFrame();

			// 쉐이더 바인딩.
			// 정점, 인덱스 버퍼 바인딩.
			// 인풋 레이아웃 바인딩.
			m_VertexShader->Bind();
			m_FragmentShader->Bind();
			m_InputLayout->Bind();
			DirectX11System::GetInstance()->GetDirectX11DeviceContext()->RSSetState(
				DirectX11System::GetInstance()->GetRasterizerState().Get()
			);

			m_VertexBuffer->Bind(m_InputLayout->GetVertexStride());
			m_IndexBuffer->Bind();

			// drawindexed
			DirectX11System::GetInstance()->GetDirectX11DeviceContext()->DrawIndexed(m_IndexBuffer->GetCount(), 0, 0);

			for (Layer* layer : m_LayerStack) // 레이어들의 update 호출.
				layer->OnUpdate();

			// ImGui GUI를 그려줌.
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			// swap buffer
			m_Window->OnUpdate();
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

	void Application::ProcessEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		// 들어온 이벤트가 WindowCloseEvent인 경우, OnWindowClose 함수를 호출하도록 함.
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_CALLBACK(&Application::OnWindowClose);

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

}