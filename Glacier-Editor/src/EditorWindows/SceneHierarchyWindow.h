#pragma once

#include "EditorWindow.h"

namespace Glacier
{
	/*
	*	씬에 배치된 오브젝트들을 보여주는 에디터 창.
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