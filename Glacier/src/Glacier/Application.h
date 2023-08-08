#pragma once

#include "Core.h"
#include "Window/Window.h"
#include "Layer/LayerStack.h"

#include "ImGui/ImGuiLayer.h"

#include "Glacier/Event/ApplicationEvent.h"
#include "Glacier/Renderer/Camera.h"
#include "Glacier/Renderer/Buffer.h"
#include "Platform/DirectX/DirectX11Common.h"
#include "Platform/DirectX/Buffer/ConstantBufferData.h"

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

		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		std::shared_ptr<ShaderBuffer> m_WorldTransformBuffer;
		std::shared_ptr<ShaderBuffer> m_CameraTransformBuffer;

		Camera m_Camera;
		WorldTransformConstant m_WorldTransformConstant;
		CameraTransformConstant m_CameraTransformConstant;

		ImGuiLayer* m_ImGuiLayer;
		bool m_IsRunning = true;
		LayerStack m_LayerStack; // application 내부에 레이어 스택을 가지고 있음.

		static Application* s_Instance;
	};

	// 클라이언트 쪽에서 정의되는 함수.
	Application* CreateApplication();
}