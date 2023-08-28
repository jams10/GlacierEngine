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
		// �����ϰ� �ִ� ���� ���� & ������ ���� ������ ������Ʈ�� ���� & ������ ������Ʈ�� Scene Root ������Ʈ�� �ƴ� ���.
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
		// �̸� ����.
		memcpy(m_InputText, WideToMultiU8(m_CurrentScene->SelectedObject->Name).c_str(), sizeof(m_InputText));
		if (ImGui::InputText("Name", m_InputText, sizeof(m_InputText), ImGuiInputTextFlags_EnterReturnsTrue))
		{
			m_CurrentScene->SelectedObject->Name = MultiU8ToWide(std::string(m_InputText));
		}
		ImGui::Text("ID : %d", m_CurrentScene->SelectedObject->ID);
	}
}