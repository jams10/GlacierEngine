#include "pch.h"
#include "DirectX11CameraController.h"

#include "Glacier/Renderer/Buffer.h"

namespace Glacier
{
	DirectX11CameraController::DirectX11CameraController(float aspectRatio)
		: CameraController(aspectRatio)
	{
		// 상수 버퍼 세팅.
		m_CameraTransformConstant.view = m_Camera.GetViewMatrix();
		m_CameraTransformConstant.proj = m_Camera.GetProjectionMatrix();
		// 상수 버퍼 생성.
		m_CameraTransformBuffer.reset(ShaderBuffer::Create(&m_CameraTransformConstant, sizeof(m_CameraTransformConstant), ShaderBufferType::VERTEX));
	}

	DirectX11CameraController::~DirectX11CameraController()
	{
	}

	void DirectX11CameraController::OnUpdate(float dt)
	{ 
		CameraController::OnUpdate(dt);

		// 상수 버퍼 업데이트 & 바인딩.
		m_CameraTransformConstant.view = m_Camera.GetViewMatrix();
		m_CameraTransformConstant.proj = m_Camera.GetProjectionMatrix();
		m_CameraTransformBuffer->UpdateData(&m_CameraTransformConstant, sizeof(m_CameraTransformConstant));
		m_CameraTransformBuffer->Bind(CameraTransformSlot);
	}

	void DirectX11CameraController::OnEvent(Event& e)
	{
		CameraController::OnEvent(e);
	}
}