#pragma once

#include "EditorWindow.h"

namespace Glacier
{
	/*
	*	���� ��ġ�� ������Ʈ���� �����ִ� ������ â.
	*/
	class SceneHierarchyWindow : public EditorWindow
	{
	public:
		SceneHierarchyWindow();
		~SceneHierarchyWindow();

		virtual void Update(float dt) override;
		virtual void Render() override;

		void SetCurrentScene(const std::shared_ptr<Scene>& scene);
		void DisplayObjects(std::shared_ptr<Object>& object);
		void OnRightClickedBackground();

	private:
		bool m_HasSelectedObject;
		std::shared_ptr<Scene> m_CurrentScene;
		std::shared_ptr<Object> m_SelectedObject;
	};
}