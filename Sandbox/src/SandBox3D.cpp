#include "SandBox3D.h"
#include "imgui.h"

SandBox3D::SandBox3D()
	: Layer("SandBox3D")
{
}

void SandBox3D::OnAttach()
{
	// ī�޶� ����.
	m_SceneCameraController.reset(Glacier::CameraController::Create(1280.f / 720.f));

	// �� ����.
	m_Model = std::make_shared<Glacier::Model>(Glacier::MeshGenerator::MakeSqaure());

	// �ؽ��� �ڿ� ����.
	m_TextureResource = Glacier::Texture2D::Create(L"../Resources/Texture/rabbit.png");

	// Material ����.
	m_Material.reset(Glacier::Material::Create());
	m_Material->AddTexture(m_TextureResource);
	m_Material->SetPipelineState(Glacier::TexureSamplingPipelineState);
	
	m_Model->SetMaterial(m_Material);
}

void SandBox3D::OnDetach()
{
}

void SandBox3D::OnUpdate(float dt)
{
	m_SceneCameraController->OnUpdate(dt);

	Glacier::Vector3 rotation = m_Model->GetTransform()->GetRotation();

	if (Glacier::Input::IsKeyPressed(GR_VK_RIGHT))
		rotation.y += dt;

	m_Model->GetTransform()->SetRotation(rotation.x, rotation.y, rotation.z);

	float color[4] = { 0.1f, 0.1f, 0.1f, 1 };
	Glacier::RenderCommand::SetClearColor(color);
	Glacier::RenderCommand::Clear();

	Glacier::Renderer::BeginRenderScene(); // set render target, viewport.


	// ����, �ε��� ���� ���ε�. draw indexed ȣ��.
	Glacier::Renderer::Submit(m_Model);
}

void SandBox3D::OnImGuiRender()
{
	
}

void SandBox3D::OnEvent(Glacier::Event& e)
{
	m_SceneCameraController->OnEvent(e);
}
