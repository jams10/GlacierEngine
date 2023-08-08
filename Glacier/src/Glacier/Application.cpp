#include "pch.h"
#include "Application.h"

#include "Glacier/Renderer/Renderer.h"
#include "Platform/DirectX/DirectX11Device.h"
#include "Platform/DirectX/Buffer/DirectX11ConstantBuffer.h"

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

		// ��� ���� ����.
		m_WorldTransformConstant.world = Matrix::CreateTranslation(Vector3::Zero);
		m_CameraTransformConstant.view = m_Camera.GetViewMatrix();
		m_CameraTransformConstant.proj = m_Camera.GetProjectionMatrix();

		m_WorldTransformBuffer.reset(ShaderBuffer::Create(&m_WorldTransformConstant, sizeof(m_WorldTransformConstant), ShaderBufferType::VERTEX));
		m_CameraTransformBuffer.reset(ShaderBuffer::Create(&m_CameraTransformConstant, sizeof(m_CameraTransformConstant), ShaderBufferType::VERTEX));
		m_Camera.SetAspectRatio(1280.f / 720.f);
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
			m_Camera.SetPosition(Vector3(0.0f, 0.0, -2.0f));
			m_Camera.Update();
			m_CameraTransformConstant.view = m_Camera.GetViewMatrix();
			m_CameraTransformConstant.proj = m_Camera.GetProjectionMatrix();
			m_CameraTransformBuffer->UpdateData(&m_CameraTransformConstant, sizeof(m_CameraTransformConstant));

			std::vector<ID3D11Buffer*> vsConstantBuffers;
			DirectX11ConstantBuffer* b1 = reinterpret_cast<DirectX11ConstantBuffer*>(m_WorldTransformBuffer.get());
			DirectX11ConstantBuffer* b2 = reinterpret_cast<DirectX11ConstantBuffer*>(m_CameraTransformBuffer.get());
			if (b1->GetBufferType() == ShaderBufferType::VERTEX)
			{
				vsConstantBuffers.push_back(b1->GetGPUBuffer().Get());
			}
			if (b2->GetBufferType() == ShaderBufferType::VERTEX)
			{
				vsConstantBuffers.push_back(b2->GetGPUBuffer().Get());
			}
			
			RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
			RenderCommand::Clear();

			Renderer::BeginRenderScene(); // set render target, viewport.

			Glacier::vertexColorPipelineState.Bind();

			DirectX11Device::GetDeviceContext()->VSSetConstantBuffers(0, (UINT)vsConstantBuffers.size(), vsConstantBuffers.data());

			Renderer::Submit(m_VertexBuffer, m_IndexBuffer, Glacier::vertexColorPipelineState.m_InputLayout);

			for (Layer* layer : m_LayerStack) // ���̾���� update ȣ��.
				layer->OnUpdate();

			// ImGui GUI�� �׷���.
			//m_ImGuiLayer->Begin();
			//for (Layer* layer : m_LayerStack)
			//	layer->OnImGuiRender();
			//m_ImGuiLayer->End();

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