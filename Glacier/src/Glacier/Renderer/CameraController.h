#pragma once

#include "Glacier/Core.h"
#include "Camera.h"

#include "Glacier/Event/ApplicationEvent.h"
#include "Glacier/Event/MouseEvent.h"

namespace Glacier
{
	class CameraController
	{
	public:
		CameraController(float aspectRatio);

		void OnUpdate(float dt);
		void OnEvent(Event& e);

		Camera& GetCamera() { return m_Camera; }
		const Camera& GetCamera() const { return m_Camera; }

	private:
		bool OnMouseWheelUp(MouseWheelUpEvent& e);
		bool OnMouseWheelDown(MouseWheelDownEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

	private:
		Camera m_Camera;
		float m_AspectRatio;
		float m_ZoomFactor = 1.0f; // ortho 카메라 zoom에 사용. 
		float m_ZoomSpeed = 5.0f;  // perspective 카메라 zoom에 사용.

		bool m_CanRotate = false;
	};
}