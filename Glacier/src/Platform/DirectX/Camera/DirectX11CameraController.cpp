#include "pch.h"
#include "DirectX11CameraController.h"

#include "Glacier/Renderer/Buffer.h"

namespace Glacier
{
	DirectX11CameraController::DirectX11CameraController(float aspectRatio)
		: CameraController(aspectRatio)
	{
		// ��� ���� ����.
		m_CameraTransformConstant.view = m_Camera.GetViewMatrix();
		m_CameraTransformConstant.proj = m_Camera.GetProjectionMatrix();
		// ��� ���� ����.
		m_CameraTransformBuffer.reset(ShaderBuffer::Create(&m_CameraTransformConstant, sizeof(m_CameraTransformConstant), ShaderBufferType::VERTEX));
	}

	DirectX11CameraController::~DirectX11CameraController()
	{
	}

	void DirectX11CameraController::OnUpdate(float dt)
	{ 
		CameraController::OnUpdate(dt);

		// ��� ���� ������Ʈ & ���ε�.
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