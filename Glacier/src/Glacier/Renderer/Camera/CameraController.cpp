#include "pch.h"
#include "CameraController.h"

#include "Glacier/Input/Input.h"
#include "Glacier/Input/InputKeys.h"

#include "Glacier/Renderer/Renderer.h"
#include "Glacier/Renderer/Buffer.h"

namespace Glacier
{
	CameraController::CameraController(float aspectRatio)
		:m_Camera(aspectRatio)
	{
		// 상수 버퍼 세팅.
		m_CameraTransformConstant.view = m_Camera.GetViewMatrix();
		m_CameraTransformConstant.proj = m_Camera.GetProjectionMatrix();

		m_ConstantBuffer.reset(Glacier::ShaderBuffer::Create(&m_CameraTransformConstant, sizeof(m_CameraTransformConstant), ShaderBufferType::VERTEX));
	}

	void CameraController::OnUpdate(float dt)
	{
		if (Input::IsKeyPressed(GR_VK_W))
			m_Camera.MoveForward(dt);
		else if (Input::IsKeyPressed(GR_VK_S))
			m_Camera.MoveForward(-dt);

		if (Input::IsKeyPressed(GR_VK_D))
			m_Camera.MoveRight(dt);
		else if (Input::IsKeyPressed(GR_VK_A))
			m_Camera.MoveRight(-dt);

		if (m_CanRotate)
		{
			if (Input::IsKeyPressed(GR_VK_Q))
				m_Camera.TurnRight(-dt);
			if (Input::IsKeyPressed(GR_VK_E))
				m_Camera.TurnRight(dt);
		}

		m_Camera.UpdateDirection();

		// 상수 버퍼 업데이트 & 바인딩.
		m_CameraTransformConstant.view = m_Camera.GetViewMatrix();
		m_CameraTransformConstant.proj = m_Camera.GetProjectionMatrix();
		m_ConstantBuffer->UpdateData(&m_CameraTransformConstant, sizeof(m_CameraTransformConstant));
		m_ConstantBuffer->Bind(CameraTransformSlot);
	}

	void CameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseWheelUpEvent>(BIND_EVENT_CALLBACK(&CameraController::OnMouseWheelUp));
		dispatcher.Dispatch<MouseWheelDownEvent>(BIND_EVENT_CALLBACK(&CameraController::OnMouseWheelDown));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_CALLBACK(&CameraController::OnWindowResized));
	}

	bool CameraController::OnMouseWheelUp(MouseWheelUpEvent& e)
	{
		if (m_Camera.m_UsePerspectiveProjection)
		{
			float fov = m_Camera.GetFov();
			fov -= m_ZoomSpeed;
			fov = std::max(fov, 10.f);
			m_Camera.SetFov(fov);
		}
		else
		{
			m_ZoomFactor -= 0.1f;
			m_ZoomFactor = std::max(m_ZoomFactor, 0.1f);
			m_Camera.SetOrthoZoomLevel(m_ZoomFactor);
		}
		return false;
	}

	bool CameraController::OnMouseWheelDown(MouseWheelDownEvent& e)
	{
		if (m_Camera.m_UsePerspectiveProjection)
		{
			float fov = m_Camera.GetFov();
			fov += m_ZoomSpeed;
			fov = std::min(fov, 60.f);
			m_Camera.SetFov(fov);
		}
		else
		{
			m_ZoomFactor += 0.1f;
			m_ZoomFactor = std::max(m_ZoomFactor, 1.0f);
			m_Camera.SetOrthoZoomLevel(m_ZoomFactor);
		}
		return false;
	}

	bool CameraController::OnWindowResized(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0) return false;

		float aspectRatio = static_cast<float>(e.GetWidth()) / static_cast<float>(e.GetHeight());
		m_Camera.SetAspectRatio(aspectRatio);
		return false;
	}
}