#include "SceneHierarchyWindow.h"
#include "imgui.h"

namespace Glacier
{
	SceneHierarchyWindow::SceneHierarchyWindow()
	{
	}

	SceneHierarchyWindow::~SceneHierarchyWindow()
	{
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

	void SceneHierarchyWindow::SetCurrentScene(std::shared_ptr<Scene> scene)
	{
		m_CurrentScene = scene;
	}

	// hierarchy â�� ���� ��ġ�� ������Ʈ���� ǥ���ϴ� �۾��� ó���ϴ� �Լ�.
	void SceneHierarchyWindow::DisplayObjects(std::shared_ptr<Object>& object)
	{
		// ������ ������Ʈ �׸� ���̶���Ʈ ȿ���� �ֱ� ���� ������ ������Ʈ�� ��� �ܰ迡���� ImGuiTreeNodeFlags_Selected�� �߰��� �÷��׸� ���.
		ImGuiTreeNodeFlags flag = ImGuiTreeNodeFlags_DefaultOpen;
		if (m_CurrentScene->SelectedObject && m_CurrentScene->SelectedObject->ID == object->ID)
			flag |= ImGuiTreeNodeFlags_Selected;

		bool nodeOpen = ImGui::TreeNodeEx(WideToMultiU8(object->Name).c_str(), flag);
		if (ImGui::IsItemClicked(ImGuiMouseButton_Right) || ImGui::IsItemClicked(ImGuiMouseButton_Left))
		{
			m_CurrentScene->SelectedObject = object; // ������ ���콺 Ŭ�� �� Ŭ���� ������Ʈ�� ����.
		}

		if (m_CurrentScene->SelectedObject)
		{
			if (ImGui::BeginPopupContextItem()) 
			{
				if (ImGui::MenuItem("Create Object")) 
				{
					m_CurrentScene->AddObject(m_CurrentScene->SelectedObject);
				}
				if (m_CurrentScene->SelectedObject->ID != 0 && ImGui::MenuItem("Delete Object"))
				{
					m_CurrentScene->RemoveObject(m_CurrentScene->SelectedObject->ID);
					object = nullptr;
					m_CurrentScene->SelectedObject = nullptr;
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

	// hierarchy â�� ����� ������ ���콺 Ŭ�� ���� �� �۾��� ó���ϴ� �Լ�.
	void SceneHierarchyWindow::OnRightClickedBackground()
	{
		// ����� Ŭ���ߴ��� ���θ� Ȯ���Ͽ� �˾� �޴� ǥ�� ���� ����.
		if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
		{
			ImGui::OpenPopup("BackgroundContextMenu");
			m_CurrentScene->SelectedObject = nullptr;
		}

		// ��� Ŭ�� �� ǥ�õǴ� ���ؽ�Ʈ �޴�.
		if (ImGui::BeginPopup("BackgroundContextMenu")) 
		{
			if (ImGui::MenuItem("Create Empty Object")) 
			{
				// ���ο� �� ������Ʈ ���� ��� ����.
				m_CurrentScene->AddObject(m_CurrentScene->GetSceneRootObject());
			}
			ImGui::EndPopup();
		}
	}
}