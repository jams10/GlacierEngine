#pragma once

#include "EditorWindow.h"

namespace Glacier
{
	/*
	*	오브젝트를 선택 했을 때 선택한 오브젝트의 정보를 보여주는 창.
	*/
	class ObjectPropertyWindow : public EditorWindow
	{
	public:
		ObjectPropertyWindow();
		~ObjectPropertyWindow();

		virtual void Update(float dt) override;
		virtual void Render() override;

		void SetCurrentScene(std::shared_ptr<Scene> scene);

	private:
		void PrintAndChangeObjectName();

	private:
		std::shared_ptr<Scene> m_CurrentScene;
		char m_InputText[100];
	};
}