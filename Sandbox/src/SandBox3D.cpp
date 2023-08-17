#include "SandBox3D.h"
#include "imgui.h"

SandBox3D::SandBox3D()
	: Layer("SandBox3D"), m_CameraController(1280.f / 720.f)
{
}

void SandBox3D::OnAttach()
{
	m_Model = std::make_shared<Glacier::Model>(Glacier::MeshGenerator::MakeSqaure());

	// �ؽ��� �ڿ� ����.
	m_TextureResource = Glacier::Texture2D::Create(L"../Resources/Texture/rabbit.png");

	// Material ����.
	m_Material.reset(Glacier::Material::Create());
	m_Material->AddTexture(m_TextureResource);
	m_Material->SetPipelineState(Glacier::TexureSamplingPipelineState);
	
	m_Model->SetMaterial(m_Material);

	// ��� ���� ����.
	m_CameraTransformConstant.view = m_CameraController.GetCamera().GetViewMatrix();
	m_CameraTransformConstant.proj = m_CameraController.GetCamera().GetProjectionMatrix();

	m_CameraTransformBuffer.reset(Glacier::ShaderBuffer::Create(&m_CameraTransformConstant, sizeof(m_CameraTransformConstant), Glacier::ShaderBufferType::VERTEX));
}

void SandBox3D::OnDetach()
{
}

void SandBox3D::OnUpdate(float dt)
{
	m_CameraController.OnUpdate(dt);

	Glacier::Vector3 rotation = m_Model->GetTransform()->GetRotation();

	if (Glacier::Input::IsKeyPressed(GR_VK_RIGHT))
		rotation.y += dt;

	m_Model->GetTransform()->SetRotation(rotation.x, rotation.y, rotation.z);

	float color[4] = { 0.1f, 0.1f, 0.1f, 1 };
	Glacier::RenderCommand::SetClearColor(color);
	Glacier::RenderCommand::Clear();

	Glacier::Renderer::BeginRenderScene(); // set render target, viewport.

	// ��� ���� ������Ʈ & ���ε�.
	m_CameraTransformConstant.view = m_CameraController.GetCamera().GetViewMatrix();
	m_CameraTransformConstant.proj = m_CameraController.GetCamera().GetProjectionMatrix();
	m_CameraTransformBuffer->UpdateData(&m_CameraTransformConstant, sizeof(m_CameraTransformConstant));
	m_CameraTransformBuffer->Bind(1);

	// ����, �ε��� ���� ���ε�. draw indexed ȣ��.
	Glacier::Renderer::Submit(m_Model);
}

void SandBox3D::OnImGuiRender()
{
	
}

void SandBox3D::OnEvent(Glacier::Event& e)
{
	m_CameraController.OnEvent(e);
}
