#pragma once

#include "Glacier/Core.h"

#include "Glacier/Event/ApplicationEvent.h"
#include "Glacier/Event/MouseEvent.h"

#include "SimpleMath.h"

namespace Glacier
{
	using DirectX::SimpleMath::Vector3;
	using DirectX::SimpleMath::Matrix;

	class GLACIER_API Camera
	{
	public:
		Camera(float aspectRatio);

		Matrix GetViewMatrix() const;
		Matrix GetProjectionMatrix() const;

		inline void SetFov(float fov) { m_Fov = fov; }
		inline void SetAspectRatio(float aspectRatio) { m_AspectRatio = aspectRatio; }
		inline void SetMoveSpeed(float speed) { m_MoveSpeed = speed; }
		inline void SetRotateSpeed(float speed) { m_RotateSpeed = speed; }
		inline void SetOrthoZoomLevel(float level) { m_ZoomLevel = level; }

		inline float GetFov() { return m_Fov; }

		void MoveForward(float dt);
		void MoveRight(float dt);
		void MoveUp(float dt);
		void TurnRight(float dt);
		void LookUp(float dt);
		void UpdateDirection();

		bool m_UsePerspectiveProjection = true;

	private:
		// ī�޶� Ʈ������.
		Vector3 m_Position = Vector3(0.0f, 0.0f, -2.0f);
		Vector3 m_ViewDir = Vector3(0.0f, 0.0f, 1.0f);  // z�� ���� ���� �ٶ�.
		Vector3 m_UpDir = Vector3(0.0f, 1.0f, 0.0f);    // up vector ����.
		Vector3 m_RightDir = Vector3(1.0f, 0.0f, 0.0f); // �޼� ��ǥ�迡���� x�� ���� ������ ������.
		float m_Pitch = 0.f;
		float m_Yaw = 0.f;

		// Projection ��ȯ ��� ���� ����.
		float m_Fov = 90.f;
		float m_AspectRatio = 16.f / 9.f;
		float m_NearZ = 0.01f;
		float m_FarZ = 100.0f;
		float m_ZoomLevel = 1.0f;

		float m_MoveSpeed = 1.0f;
		float m_RotateSpeed = 1.0f;
	};
}