#include "SandBox3D.h"
#include "imgui.h"

SandBox3D::SandBox3D()
	: Layer("SandBox3D"), m_CameraController(1280.f / 720.f)
{
}

void SandBox3D::OnAttach()
{
	m_Model = std::make_shared<Glacier::Model>(Glacier::MeshGenerator::MakeSqaure());

	// 텍스쳐 자원 생성.
	m_TextureResource = Glacier::Texture2D::Create(L"../Resources/Texture/rabbit.png");

	// Material 생성.
	m_Material.reset(Glacier::Material::Create());
	m_Material->AddTexture(m_TextureResource);
	m_Material->SetPipelineState(Glacier::TexureSamplingPipelineState);
	
	m_Model->SetMaterial(m_Material);

	// 상수 버퍼 세팅.
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

	//Glacier::TexureSamplingPipelineState->Bind();

	// 상수 버퍼 업데이트 & 바인딩.
	m_CameraTransformConstant.view = m_CameraController.GetCamera().GetViewMatrix();
	m_CameraTransformConstant.proj = m_CameraController.GetCamera().GetProjectionMatrix();
	//m_WorldTransformBuffer->UpdateData(&m_WorldTransformConstant, sizeof(m_WorldTransformBuffer));
	m_CameraTransformBuffer->UpdateData(&m_CameraTransformConstant, sizeof(m_CameraTransformConstant));
	m_WorldTransformBuffer->Bind(0);
	m_CameraTransformBuffer->Bind(1);

	// 정점, 인덱스 버퍼 바인딩. draw indexed 호출.
	//Glacier::Renderer::Submit(m_VertexBuffer, m_IndexBuffer, Glacier::TexureSamplingPipelineState.m_InputLayout);
	Glacier::Renderer::Submit(m_Model);
}

void SandBox3D::OnImGuiRender()
{
	
}

void SandBox3D::OnEvent(Glacier::Event& e)
{
	m_CameraController.OnEvent(e);
}
