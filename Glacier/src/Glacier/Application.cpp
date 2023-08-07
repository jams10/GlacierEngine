#include "pch.h"
#include "Application.h"

#include "Glacier/Renderer/Renderer.h"
#include "Platform/DirectX/DirectX11Device.h"

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

		// OPENGL�� ��� �� �ð� ����, DirectX������ �� �ð� ������ ��� �޸��� ��Ÿ����, rasterizer state�� backfaceculling�� ����ϴ� ��쿡
		// rasterization �ܰ迡�� ���͸� �ǰ� ��.
		// ���� �׽�Ʈ�� ��� pixel shader ������ output merger �ܰ迡�� ����.
		float vertices[3 * 6] = {
			 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		};
		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		BufferLayout layout = {
			{ ShaderDataType::Float3, "Position" },
			{ ShaderDataType::Float3, "Color" }
		};
		m_VertexBuffer->SetLayout(layout);

		uint32 indices[3] = { 0,1,2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32)));

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
			RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
			RenderCommand::Clear();

			Renderer::BeginRenderScene(); // set render target, viewport.

			Glacier::vertexColorPipelineState.Bind();

			Renderer::Submit(m_VertexBuffer, m_IndexBuffer, Glacier::vertexColorPipelineState.m_InputLayout);

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