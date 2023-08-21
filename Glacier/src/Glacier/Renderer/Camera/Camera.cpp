#include "pch.h"
#include "Camera.h"

namespace Glacier
{
	Camera::Camera(float aspectRatio)
		:m_AspectRatio(aspectRatio)
	{
	}

	Matrix Camera::GetViewMatrix() const
	{
		// view 변환 행렬의 목적은 물체들의 좌표계를 우리가 물체들을 바라보는 카메라, 시점을 기준 공간 좌표계로 변환하는 것.
		// 직관적으로 생각하면 카메라가 왼쪽으로 이동하면, 물체들은 오른쪽으로 이동해야 함. (반대 방향으로 translation)
		// 회전 또한 카메라가 왼쪽으로 회전하면, 물체들은 오른쪽으로 회전해야 함. (반대 방향으로 rotation)
		// pitch의 경우 시점을 아래로 내리면 값이 증가함. 
		// 그러면 시점을 위로 올리면 -pitch 값이 됨. 여기서 우리가 시점을 위로 올렸을 때 물체들은 아래로 내려가도록 -1을 또 곱하면 pitch가 됨.
		return  (Matrix::CreateTranslation(-this->m_Position) *
			Matrix::CreateRotationY(-this->m_Yaw) *
			Matrix::CreateRotationX(this->m_Pitch)).Transpose();
	}

	Matrix Camera::GetProjectionMatrix() const
	{
		// 원근 투영을 사용하는 경우 XMMatrixPerspectiveFovLH(), 직교 투영을 사용하는 경우 XMMatrixOrthographicOffCenterLH() 함수를 통해 투영 행렬 구함.
		Matrix proj = m_UsePerspectiveProjection
			? DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(m_Fov),
				m_AspectRatio, m_NearZ, m_FarZ)
			  : DirectX::XMMatrixOrthographicOffCenterLH(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel,
				  m_ZoomLevel, m_NearZ, m_FarZ);
		return proj.Transpose(); // DirectX의 경우 row-major 행렬을 사용하기 때문에 column-major를 사용하는 hlsl 쉐이더로 데이터를 보낼 때는 전치 시켜서 보내줘야 함.
	}

	void Camera::UpdateDirection()
	{
		// 현재 사용하고 있는 좌표계는 z-forward 왼손 좌표계.
		// 카메라 초기 방향은 z축 양의 방향을 바라 보도록 했기 때문에 yaw 회전에 따라 달라지는 카메라가 보는 방향을 다시 계산함.
		// 카메라가 보는 방향으로 이동할 수 있도록 pitch 값 회전도 추가 했음.
		m_ViewDir = Vector3::Transform(Vector3(0.0f, 0.0f, 1.0f), Matrix::CreateRotationX(-this->m_Pitch));
		m_ViewDir = Vector3::Transform(m_ViewDir, Matrix::CreateRotationY(this->m_Yaw));
		// 카메라 시점 벡터와 up 벡터를 외적하여 오른쪽 방향 벡터를 얻어줌. view 변환 행렬 생성 시 필요.
		m_RightDir = m_UpDir.Cross(m_ViewDir);
		m_RightDir = m_UpDir.Cross(m_ViewDir);
		// 여기서 viewDir과 upDir 벡터는 단위 벡터임이 보장되지만, 단위 벡터 끼리 수직을 이루지 않으면 외적의 결과가 1보다 작을 수 있음. 따라서 정규화를 해줌.
		// 더 자세히 설명하면, 두 벡터가 단위 벡터이면, 외적 결과 벡터의 크기는 두 벡터의 sin 값이 되기 때문에 두 벡터가 수직인 경우 sin = 1로 단위 벡터가 되지만,
		// 두 벡터가 30도를 이루는 경우에는 결과 벡터의 크기가 0.5가 됨.
		m_RightDir.Normalize();
	}

	void Camera::MoveForward(float dt)
	{
		m_Position += m_ViewDir * m_MoveSpeed * dt;
	}

	void Camera::MoveRight(float dt)
	{
		m_Position += m_RightDir * m_MoveSpeed * dt;
	}

	void Camera::MoveUp(float dt)
	{
		m_Position += m_UpDir * m_MoveSpeed * dt;
	}

	void Camera::TurnRight(float dt)
	{
		m_Yaw += m_RotateSpeed * dt;
	}

	void Camera::LookUp(float dt)
	{
		m_Pitch -= m_RotateSpeed * dt;
	}
}