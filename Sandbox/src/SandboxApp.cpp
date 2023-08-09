#include <Glacier.h>

class ExampleLayer : public Glacier::Layer
{
public:
	ExampleLayer() : Layer("Example"), m_CameraController(1280.f / 720.f)
	{
		// OPENGL의 경우 반 시계 방향, DirectX에서는 반 시계 방향일 경우 뒷면을 나타내며, rasterizer state가 backfaceculling을 사용하는 경우에
		// rasterization 단계에서 필터링 되게 됨.
		// 깊이 테스트의 경우 pixel shader 이후의 output merger 단계에서 수행.
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

		// 텍스쳐 자원 생성.
		m_TextureResource = Glacier::Texture2D::Create(L"../Resources/Texture/rabbit.png");

		// 상수 버퍼 세팅.
		m_WorldTransformConstant.world = Glacier::Matrix::CreateTranslation(Glacier::Vector3::Zero);
		//m_CameraTransformConstant.view = m_CameraControllerm_Camera.GetViewMatrix();
		//m_CameraTransformConstant.proj = m_CameraController.m_Camera.GetProjectionMatrix();
		m_CameraTransformConstant.view = m_CameraController.GetCamera().GetViewMatrix();
		m_CameraTransformConstant.proj = m_CameraController.GetCamera().GetProjectionMatrix();

		m_WorldTransformBuffer.reset(Glacier::ShaderBuffer::Create(&m_WorldTransformConstant, sizeof(m_WorldTransformConstant), Glacier::ShaderBufferType::VERTEX));
		m_CameraTransformBuffer.reset(Glacier::ShaderBuffer::Create(&m_CameraTransformConstant, sizeof(m_CameraTransformConstant), Glacier::ShaderBufferType::VERTEX));
	}

	void OnUpdate(float dt) override
	{
		m_CameraController.OnUpdate(dt);

		float color[4] = { 0.1f, 0.1f, 0.1f, 1 };
		Glacier::RenderCommand::SetClearColor(color);
		Glacier::RenderCommand::Clear();

		Glacier::Renderer::BeginRenderScene(); // set render target, viewport.
		
		// 텍스쳐 샘플링 쉐이더를 사용하는 파이프라인으로 세팅.
		Glacier::TexureSamplingPipelineState.Bind();

		// 텍스쳐 자원 바인딩.
		m_TextureResource->Bind(0);

		// 상수 버퍼 업데이트 & 바인딩.
		m_CameraTransformConstant.view = m_CameraController.GetCamera().GetViewMatrix();
		m_CameraTransformConstant.proj = m_CameraController.GetCamera().GetProjectionMatrix();
		//m_WorldTransformBuffer->UpdateData(&m_WorldTransformConstant, sizeof(m_WorldTransformBuffer));
		m_CameraTransformBuffer->UpdateData(&m_CameraTransformConstant, sizeof(m_CameraTransformConstant));
		m_WorldTransformBuffer->Bind(0);
		m_CameraTransformBuffer->Bind(1);

		// 정점, 인덱스 버퍼 바인딩. draw indexed 호출.
		Glacier::Renderer::Submit(m_VertexBuffer, m_IndexBuffer, Glacier::TexureSamplingPipelineState.m_InputLayout);
	}

	void OnEvent(Glacier::Event& event) override
	{	
		m_CameraController.OnEvent(event);
	}

private:
	std::shared_ptr<Glacier::VertexBuffer> m_VertexBuffer;
	std::shared_ptr<Glacier::IndexBuffer> m_IndexBuffer;
	std::shared_ptr<Glacier::ShaderBuffer> m_WorldTransformBuffer;
	std::shared_ptr<Glacier::ShaderBuffer> m_CameraTransformBuffer;
	std::shared_ptr<Glacier::Texture2D> m_TextureResource;

	Glacier::CameraController m_CameraController;

	Glacier::WorldTransformConstant m_WorldTransformConstant;
	Glacier::CameraTransformConstant m_CameraTransformConstant;
};

class Sandbox : public Glacier::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Glacier::Application* Glacier::CreateApplication()
{
	return new Sandbox();
}
