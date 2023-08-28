#include "ObjectPropertyWindow.h"
#include "imgui.h"

namespace Glacier
{
	ObjectPropertyWindow::ObjectPropertyWindow()
	{
		m_CurrentScene = nullptr;
		memset(m_InputText, 0, sizeof(m_InputText));
	}

	ObjectPropertyWindow::~ObjectPropertyWindow()
	{
		m_CurrentScene = nullptr;
	}

	void ObjectPropertyWindow::Update(float dt)
	{

	}

	void ObjectPropertyWindow::Render()
	{
		ImGui::Begin("Object Property");
		// 참조하고 있는 씬이 존재 & 씬에서 현재 선택한 오브젝트가 있음 & 선택한 오브젝트가 Scene Root 오브젝트가 아닌 경우.
		if (m_CurrentScene && m_CurrentScene->SelectedObject && m_CurrentScene->SelectedObject->ID != 0)
		{
			PrintAndChangeObjectName();
		}
		ImGui::End();
	}

	void ObjectPropertyWindow::SetCurrentScene(std::shared_ptr<Scene> scene)
	{
		m_CurrentScene = scene;
	}

	void ObjectPropertyWindow::PrintAndChangeObjectName()
	{
		// 이름 변경.
		memcpy(m_InputText, WideToMultiU8(m_CurrentScene->SelectedObject->Name).c_str(), sizeof(m_InputText));
		if (ImGui::InputText("Name", m_InputText, sizeof(m_InputText), ImGuiInputTextFlags_EnterReturnsTrue))
		{
			m_CurrentScene->SelectedObject->Name = MultiU8ToWide(std::string(m_InputText));
		}
		ImGui::Text("ID : %d", m_CurrentScene->SelectedObject->ID);
	}
}