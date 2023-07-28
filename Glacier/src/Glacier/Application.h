#pragma once

#include "Core.h"
#include "Window/Window.h"
#include "Layer/LayerStack.h"

#include "ImGui/ImGuiLayer.h"
#include "Renderer/GraphicsContext.h"

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
	private:
		std::unique_ptr<Window> m_Window;
		std::unique_ptr<GraphicsContext> m_Context;

		ImGuiLayer* m_ImGuiLayer;
		bool m_IsRunning = true;
		LayerStack m_LayerStack; // application 내부에 레이어 스택을 가지고 있음.

		static Application* s_Instance;
	};

	// 클라이언트 쪽에서 정의되는 함수.
	Application* CreateApplication();
}