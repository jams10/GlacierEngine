#include "EditorLayer.h"
#include "imgui.h"

namespace Glacier
{
	EditorLayer::EditorLayer()
		: Layer("EditorLayer")
	{
	}

	void EditorLayer::OnAttach()
	{
		// 카메라 생성.
		m_SceneCameraController.reset(Glacier::CameraController::Create(1280.f / 720.f));

		// 모델 생성.
		m_Model = std::make_shared<Glacier::Model>(Glacier::MeshGenerator::MakeCube());
		m_Model2 = std::make_shared<Glacier::Model>(Glacier::MeshGenerator::MakeCube());

		// 텍스쳐 자원 생성.
		m_TextureResource = Glacier::Texture2D::Create(L"../Resources/Texture/rabbit.png");

		// Material 생성.
		m_Material.reset(Glacier::Material::Create());
		m_Material->AddTexture(m_TextureResource);
		m_Material->SetPipelineState(Glacier::TexureSamplingPipelineState);

		m_Model->SetMaterial(m_Material);
		m_Model2->SetMaterial(m_Material);
	}

	void EditorLayer::OnDetach()
	{
	}

	void EditorLayer::OnUpdate(float dt)
	{
		m_SceneCameraController->OnUpdate(dt);

		Glacier::Vector3 rotation = m_Model->GetTransform()->GetRotation();

		if (Glacier::Input::IsKeyPressed(GR_VK_RIGHT))
			rotation.y += dt;

		m_Model->GetTransform()->SetRotation(rotation.x, rotation.y, rotation.z);

		//float color[4] = { 0.1f, 0.1f, 0.1f, 1 };
		//Glacier::RenderCommand::SetClearColor(color);
		//Glacier::RenderCommand::Clear();

		Glacier::Renderer::BeginRenderScene(); // set render target, viewport.
		//Glacier::Renderer::BeginRenderUI();

		// 정점, 인덱스 버퍼 바인딩. draw indexed 호출.
		Glacier::Renderer::Submit(m_Model);
		Glacier::Renderer::Submit(m_Model2);

		Glacier::Renderer::EndRenderScene(); // set render target, viewport.

	}

#pragma region GUI Windows
	void StatWindow()
	{
		ImGui::Begin("Stats");

		Glacier::Stat stats = Glacier::Renderer::GetStats();
		ImGui::Text("Scene Stats");
		ImGui::Text("Draw Calls : %d", stats.DrawCalls);
		ImGui::Text("Quads : %d", stats.Quads);
		ImGui::Text("Vertices : %d", stats.Vertices);
		ImGui::Text("Indices : %d", stats.Indices);

		ImGui::End();
	}

	void EditorLayer::SceneViewPort()
	{
		ImGui::Begin("Viewport");

		ImVec2 windowSize = ImGui::GetContentRegionAvail();
		ImVec2 windowPosition = ImGui::GetCursorScreenPos();

		uint32 width = windowSize.x;
		uint32 height = windowSize.y;
		m_SceneCameraController->SetAspectRation((float)width / (float)height);

		ImGui::Image(RenderCommand::GetSceneRenderedTexture(), ImVec2{windowSize.x, windowSize.y});
		//ImGui::Text("Size : %f , %f", m_windowData.windowSize.x, m_windowData.windowSize.y);

		ImGui::End();
	}

#pragma endregion

	void EditorLayer::OnImGuiRender()
	{
		// Imgui docking을 사용함.
		static bool dockingEnabled = true;
		if (dockingEnabled)
		{
			static bool dockspaceOpen = true;
			static bool opt_fullscreen_persistant = true;
			bool opt_fullscreen = opt_fullscreen_persistant;
			static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

			// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
			// because it would be confusing to have two docking targets within each others.
			ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
			if (opt_fullscreen)
			{
				ImGuiViewport* viewport = ImGui::GetMainViewport();
				ImGui::SetNextWindowPos(viewport->Pos);
				ImGui::SetNextWindowSize(viewport->Size);
				ImGui::SetNextWindowViewport(viewport->ID);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
				window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
				window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
			}

			// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
			if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
				window_flags |= ImGuiWindowFlags_NoBackground;

			// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
			// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive, 
			// all active windows docked into it will lose their parent and become undocked.
			// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise 
			// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
			ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
			ImGui::PopStyleVar();

			if (opt_fullscreen)
				ImGui::PopStyleVar(2);

			// DockSpace
			ImGuiIO& io = ImGui::GetIO();
			if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
			{
				ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
				ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
			}

			if (ImGui::BeginMenuBar())
			{
				if (ImGui::BeginMenu("File"))
				{
					// Disabling fullscreen would allow the window to be moved to the front of other windows, 
					// which we can't undo at the moment without finer window depth/z control.
					//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

					if (ImGui::MenuItem("Exit")) Glacier::Application::Get().Close();
					ImGui::EndMenu();
				}
				ImGui::EndMenuBar();
			}

			StatWindow();
			SceneViewPort();

			ImGui::End();
		}
	}

	void EditorLayer::OnEvent(Glacier::Event& e)
	{
		m_SceneCameraController->OnEvent(e);
	}
}