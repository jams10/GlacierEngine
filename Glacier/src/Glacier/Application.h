#pragma once

#include "Core/Core.h"
#include "Window/Window.h"
#include "Layer/LayerStack.h"

#include "ImGui/ImGuiLayer.h"

#include "Glacier/Event/ApplicationEvent.h"
#include "Glacier/Utils/GameTimer.h"

namespace Glacier
{
	class GLACIER_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }

		void ProcessEvent(Event& event);

	private:
		bool OnWindowClose(WindowCloseEvent event);
		bool OnWindowResize(WindowResizeEvent event);

	private:
		std::unique_ptr<Window> m_Window;

		GameTimer m_GameTimer;

		LayerStack m_LayerStack; // application 내부에 레이어 스택을 가지고 있음.
		ImGuiLayer* m_ImGuiLayer;

		bool m_IsRunning = true;		
		bool m_Minimized = false;

		static Application* s_Instance;
	};

	// 클라이언트 쪽에서 정의되는 함수.
	Application* CreateApplication();
}