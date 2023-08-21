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
		// view ��ȯ ����� ������ ��ü���� ��ǥ�踦 �츮�� ��ü���� �ٶ󺸴� ī�޶�, ������ ���� ���� ��ǥ��� ��ȯ�ϴ� ��.
		// ���������� �����ϸ� ī�޶� �������� �̵��ϸ�, ��ü���� ���������� �̵��ؾ� ��. (�ݴ� �������� translation)
		// ȸ�� ���� ī�޶� �������� ȸ���ϸ�, ��ü���� ���������� ȸ���ؾ� ��. (�ݴ� �������� rotation)
		// pitch�� ��� ������ �Ʒ��� ������ ���� ������. 
		// �׷��� ������ ���� �ø��� -pitch ���� ��. ���⼭ �츮�� ������ ���� �÷��� �� ��ü���� �Ʒ��� ���������� -1�� �� ���ϸ� pitch�� ��.
		return  (Matrix::CreateTranslation(-this->m_Position) *
			Matrix::CreateRotationY(-this->m_Yaw) *
			Matrix::CreateRotationX(this->m_Pitch)).Transpose();
	}

	Matrix Camera::GetProjectionMatrix() const
	{
		// ���� ������ ����ϴ� ��� XMMatrixPerspectiveFovLH(), ���� ������ ����ϴ� ��� XMMatrixOrthographicOffCenterLH() �Լ��� ���� ���� ��� ����.
		Matrix proj = m_UsePerspectiveProjection
			? DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(m_Fov),
				m_AspectRatio, m_NearZ, m_FarZ)
			  : DirectX::XMMatrixOrthographicOffCenterLH(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel,
				  m_ZoomLevel, m_NearZ, m_FarZ);
		return proj.Transpose(); // DirectX�� ��� row-major ����� ����ϱ� ������ column-major�� ����ϴ� hlsl ���̴��� �����͸� ���� ���� ��ġ ���Ѽ� ������� ��.
	}

	void Camera::UpdateDirection()
	{
		// ���� ����ϰ� �ִ� ��ǥ��� z-forward �޼� ��ǥ��.
		// ī�޶� �ʱ� ������ z�� ���� ������ �ٶ� ������ �߱� ������ yaw ȸ���� ���� �޶����� ī�޶� ���� ������ �ٽ� �����.
		// ī�޶� ���� �������� �̵��� �� �ֵ��� pitch �� ȸ���� �߰� ����.
		m_ViewDir = Vector3::Transform(Vector3(0.0f, 0.0f, 1.0f), Matrix::CreateRotationX(-this->m_Pitch));
		m_ViewDir = Vector3::Transform(m_ViewDir, Matrix::CreateRotationY(this->m_Yaw));
		// ī�޶� ���� ���Ϳ� up ���͸� �����Ͽ� ������ ���� ���͸� �����. view ��ȯ ��� ���� �� �ʿ�.
		m_RightDir = m_UpDir.Cross(m_ViewDir);
		m_RightDir = m_UpDir.Cross(m_ViewDir);
		// ���⼭ viewDir�� upDir ���ʹ� ���� �������� ���������, ���� ���� ���� ������ �̷��� ������ ������ ����� 1���� ���� �� ����. ���� ����ȭ�� ����.
		// �� �ڼ��� �����ϸ�, �� ���Ͱ� ���� �����̸�, ���� ��� ������ ũ��� �� ������ sin ���� �Ǳ� ������ �� ���Ͱ� ������ ��� sin = 1�� ���� ���Ͱ� ������,
		// �� ���Ͱ� 30���� �̷�� ��쿡�� ��� ������ ũ�Ⱑ 0.5�� ��.
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