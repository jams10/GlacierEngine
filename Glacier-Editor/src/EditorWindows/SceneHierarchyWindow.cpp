#include "SceneHierarchyWindow.h"
#include "imgui.h"

namespace Glacier
{
	SceneHierarchyWindow::SceneHierarchyWindow()
	{
		m_HasSelectedObject = false;
	}

	SceneHierarchyWindow::~SceneHierarchyWindow()
	{
		m_SelectedObject = nullptr;
		m_CurrentScene = nullptr;
	}

	void SceneHierarchyWindow::Update(float dt)
	{
	}

	void SceneHierarchyWindow::Render()
	{
		ImGui::Begin("Scene Hierarchy");

		if (m_CurrentScene != nullptr)
		{
			OnRightClickedBackground();
			DisplayObjects(m_CurrentScene->GetSceneRootObject());
		}

		ImGui::End();
	}

	void SceneHierarchyWindow::SetCurrentScene(const std::shared_ptr<Scene>& scene)
	{
		m_CurrentScene = scene;
	}

	// hierarchy 창에 씬에 배치된 오브젝트들을 표시하는 작업을 처리하는 함수.
	void SceneHierarchyWindow::DisplayObjects(std::shared_ptr<Object>& object)
	{
		bool nodeOpen = ImGui::TreeNodeEx(WideToMultiU8(object->Name).c_str(), ImGuiTreeNodeFlags_DefaultOpen);
		if (ImGui::IsItemClicked(ImGuiMouseButton_Right)) {
			m_SelectedObject = object; // 오른쪽 마우스 클릭 시 클릭된 오브젝트를 선택.
		}

		if (m_SelectedObject)
		{
			if (ImGui::BeginPopupContextItem()) 
			{
				if (ImGui::MenuItem("Create Object")) 
				{
					m_CurrentScene->AddObject(m_SelectedObject);
				}
				if (m_SelectedObject->ID != 0 && ImGui::MenuItem("Delete Object"))
				{
					m_CurrentScene->RemoveObject(m_SelectedObject->ID);
					object = nullptr;
					m_SelectedObject = nullptr;
				}
				ImGui::EndPopup();
			}
		}

		if (nodeOpen) 
		{
			if (object != nullptr)
			{
				for (std::shared_ptr<Object> child : object->GetChildren())
				{
					DisplayObjects(child);
					if (child == nullptr) break;
				}
			}
			ImGui::TreePop();
		}

	}

	// hierarchy 창의 배경을 오른쪽 마우스 클릭 했을 때 작업을 처리하는 함수.
	void SceneHierarchyWindow::OnRightClickedBackground()
	{
		// 배경을 클릭했는지 여부를 확인하여 팝업 메뉴 표시 여부 결정.
		if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
		{
			ImGui::OpenPopup("BackgroundContextMenu");
			m_SelectedObject = false;
		}

		// 배경 클릭 시 표시되는 컨텍스트 메뉴.
		if (ImGui::BeginPopup("BackgroundContextMenu")) 
		{
			if (ImGui::MenuItem("Create Empty Object")) 
			{
				// 새로운 빈 오브젝트 생성 기능 구현.
				m_CurrentScene->AddObject(m_CurrentScene->GetSceneRootObject());
			}
			ImGui::EndPopup();
		}
	}
}