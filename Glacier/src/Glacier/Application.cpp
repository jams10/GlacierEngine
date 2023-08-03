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

		// ������ �޽��� �߻� �� �̺�Ʈ�� ����� �Ѱ��� �� ó������ �ݹ� �Լ��� ���ڷ� ���� �Ѱ� ������ ����.
		// ������ ���� �Ŀ� �ݹ� �Լ��� ���ε� ������, ������ ���� �� WM_SIZE �޽����� �ٷ� �߻��ϰ� �Ǵµ� 
		// �� ���������� �ݹ� �Լ��� ���ε� �Ǿ� ���� �ʱ� ������ �� �Լ� ��ü�� ȣ���ϱ� ������ bad_function_call ���� �߻�.
		// ����, ������ Ŭ���� ��ü ���� ������ �ݹ� �Լ��� ���� ���ε� ����.
		m_Window = std::unique_ptr<Window>(Window::Create(BIND_EVENT_CALLBACK(&Application::ProcessEvent));			

		m_ImGuiLayer = new ImGuiLayer(); // ImGuiLayer ����.
		PushOverlay(m_ImGuiLayer);       // ImGuiLayer�� Overlay ���̾ �߰�.

		/*
		*	�ӽ� �׽�Ʈ ���� �׸���.
		*/
		//  ���� ���� ����.
		//  �ε��� ���� ����.
		//  ���̴� ����.
		//  ��ǲ ���̾ƿ� ����.

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
		// entry point �ν��Ͻ� ���� ���ŵ�.
		s_Instance = nullptr;
	}

	void Application::Run()
	{
		while (m_IsRunning)
		{
			// begin frame
			DirectX11System::GetInstance()->BeginFrame();

			// ���̴� ���ε�.
			// ����, �ε��� ���� ���ε�.
			// ��ǲ ���̾ƿ� ���ε�.
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

			for (Layer* layer : m_LayerStack) // ���̾���� update ȣ��.
				layer->OnUpdate();

			// ImGui GUI�� �׷���.
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
		// ���� �̺�Ʈ�� WindowCloseEvent�� ���, OnWindowClose �Լ��� ȣ���ϵ��� ��.
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_CALLBACK(&Application::OnWindowClose);

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

}