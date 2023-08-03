#pragma once

#include "Core.h"
#include "Window/Window.h"
#include "Layer/LayerStack.h"

#include "ImGui/ImGuiLayer.h"

#include "Glacier/Renderer/Shader.h"
#include "Glacier/Event/ApplicationEvent.h"
#include "Glacier/Renderer/Buffer.h"
#include "Glacier/Renderer/VertexLayout.h"

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

	private:
		std::unique_ptr<Window> m_Window;

		std::unique_ptr<VertexShader> m_VertexShader;
		std::unique_ptr<FragmentShader> m_FragmentShader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<VertexLayout> m_InputLayout;

		ImGuiLayer* m_ImGuiLayer;
		bool m_IsRunning = true;
		LayerStack m_LayerStack; // application ���ο� ���̾� ������ ������ ����.

		static Application* s_Instance;
	};

	// Ŭ���̾�Ʈ �ʿ��� ���ǵǴ� �Լ�.
	Application* CreateApplication();
}