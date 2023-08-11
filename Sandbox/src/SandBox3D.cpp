#include "SandBox3D.h"
#include "imgui.h"

SandBox3D::SandBox3D()
	: Layer("SandBox3D"), m_CameraController(1280.f / 720.f)
{
}

void SandBox3D::OnAttach()
{
	// OPENGL�� ��� �� �ð� ����, DirectX������ �� �ð� ������ ��� �޸��� ��Ÿ����, rasterizer state�� backfaceculling�� ����ϴ� ��쿡
	// rasterization �ܰ迡�� ���͸� �ǰ� ��.
	// ���� �׽�Ʈ�� ��� pixel shader ������ output merger �ܰ迡�� ����.
	float vertices[4 * 5] = {
		-0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f
	};
	m_VertexBuffer.reset(Glacier::VertexBuffer::Create(vertices, sizeof(vertices)));

	Glacier::BufferLayout layout = {
		{ Glacier::ShaderDataType::Float3, "Position" },
		{ Glacier::ShaderDataType::Float2, "Texcoord" }
	};
	m_VertexBuffer->SetLayout(layout);

	uint32 indices[6] = { 0,1,2,2,3,0 };
	m_IndexBuffer.reset(Glacier::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32)));

	// �ؽ��� �ڿ� ����.
	m_TextureResource = Glacier::Texture2D::Create(L"../Resources/Texture/rabbit.png");

	// ��� ���� ����.
	m_WorldTransformConstant.world = Glacier::Matrix::CreateTranslation(Glacier::Vector3::Zero);
	m_CameraTransformConstant.view = m_CameraController.GetCamera().GetViewMatrix();
	m_CameraTransformConstant.proj = m_CameraController.GetCamera().GetProjectionMatrix();

	m_WorldTransformBuffer.reset(Glacier::ShaderBuffer::Create(&m_WorldTransformConstant, sizeof(m_WorldTransformConstant), Glacier::ShaderBufferType::VERTEX));
	m_CameraTransformBuffer.reset(Glacier::ShaderBuffer::Create(&m_CameraTransformConstant, sizeof(m_CameraTransformConstant), Glacier::ShaderBufferType::VERTEX));
}

void SandBox3D::OnDetach()
{
}

void SandBox3D::OnUpdate(float dt)
{
	m_CameraController.OnUpdate(dt);

	float color[4] = { 0.1f, 0.1f, 0.1f, 1 };
	Glacier::RenderCommand::SetClearColor(color);
	Glacier::RenderCommand::Clear();

	Glacier::Renderer::BeginRenderScene(); // set render target, viewport.

	// �ؽ��� ���ø� ���̴��� ����ϴ� �������������� ����.
	Glacier::TexureSamplingPipelineState.Bind();

	// �ؽ��� �ڿ� ���ε�.
	m_TextureResource->Bind(0);

	// ��� ���� ������Ʈ & ���ε�.
	m_CameraTransformConstant.view = m_CameraController.GetCamera().GetViewMatrix();
	m_CameraTransformConstant.proj = m_CameraController.GetCamera().GetProjectionMatrix();
	//m_WorldTransformBuffer->UpdateData(&m_WorldTransformConstant, sizeof(m_WorldTransformBuffer));
	m_CameraTransformBuffer->UpdateData(&m_CameraTransformConstant, sizeof(m_CameraTransformConstant));
	m_WorldTransformBuffer->Bind(0);
	m_CameraTransformBuffer->Bind(1);

	// ����, �ε��� ���� ���ε�. draw indexed ȣ��.
	Glacier::Renderer::Submit(m_VertexBuffer, m_IndexBuffer, Glacier::TexureSamplingPipelineState.m_InputLayout);
}

void SandBox3D::OnImGuiRender()
{
	
}

void SandBox3D::OnEvent(Glacier::Event& e)
{
	m_CameraController.OnEvent(e);
}
