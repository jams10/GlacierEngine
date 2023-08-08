#pragma once

#include "Glacier/Core.h"

#include "SimpleMath.h"

namespace Glacier
{
	using DirectX::SimpleMath::Vector3;
	using DirectX::SimpleMath::Matrix;

	class GLACIER_API Camera
	{
	public:
		Camera();

		Matrix GetViewMatrix() const;
		Matrix GetProjectionMatrix() const;

		void SetAspectRatio(float aspectRatio);
		void SetPosition(Vector3 pos);
		void SetYaw(float yaw);
		void SetPitch(float pitch);
		void MoveForward(float dt);
		void MoveRight(float dt);
		void MoveUpward(float dt);

		void Update();
		void ToggleFlyingCam();

	private:
		// 카메라 트랜스폼.
		Vector3 m_Position = Vector3(0.0f, 0.0f, -2.0f);
		Vector3 m_ViewDir = Vector3(0.0f, 0.0f, 1.0f);  // z축 양의 방향 바라봄.
		Vector3 m_UpDir = Vector3(0.0f, 1.0f, 0.0f);    // up vector 고정.
		Vector3 m_RightDir = Vector3(1.0f, 0.0f, 0.0f); // 왼손 좌표계에서는 x축 양의 방향이 오른쪽.
		float m_Pitch = 0.f;
		float m_Yaw = 0.f;

		// Projection 변환 행렬 관련 변수.
		float m_ProjFovAngleY = 90.0f;
		float m_NearZ = 0.01f;
		float m_FarZ = 100.0f;
		float m_AspectRatio = 16.f / 9.f;
		bool m_UsePerspectiveProjection = true;
		bool m_UseFlyingCam = false;

		float m_Speed = 1.0f;
	};
}