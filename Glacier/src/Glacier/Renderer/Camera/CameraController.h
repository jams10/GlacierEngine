#pragma once

#include "Glacier/Core/Core.h"
#include "Camera.h"

#include "Glacier/Event/ApplicationEvent.h"
#include "Glacier/Event/MouseEvent.h"

namespace Glacier
{
	class CameraController
	{
	public:
		CameraController(float aspectRatio);
		virtual ~CameraController() {}

		virtual void OnUpdate(float dt);
		virtual void OnEvent(Event& e);

		Camera& GetCamera() { return m_Camera; }
		const Camera& GetCamera() const { return m_Camera; }
		
		void SetAspectRation(float aspectRatio) { m_Camera.SetAspectRatio(aspectRatio); }

		static CameraController* Create(float aspectRatio);

	protected:
		bool OnMouseWheelUp(MouseWheelUpEvent& e);
		bool OnMouseWheelDown(MouseWheelDownEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

	protected:
		Camera m_Camera;
		float m_AspectRatio;
		float m_ZoomFactor = 1.0f; // ortho 카메라 zoom에 사용. 
		float m_ZoomSpeed = 5.0f;  // perspective 카메라 zoom에 사용.

		bool m_CanRotate = true;
	};
}