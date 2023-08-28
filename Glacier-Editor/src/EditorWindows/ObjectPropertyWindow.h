#pragma once

#include "EditorWindow.h"

namespace Glacier
{
	/*
	*	������Ʈ�� ���� ���� �� ������ ������Ʈ�� ������ �����ִ� â.
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