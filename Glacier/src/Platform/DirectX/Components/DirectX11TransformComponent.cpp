#include "pch.h"
#include "DirectX11TransformComponent.h"

namespace Glacier
{
	DirectX11TransformComponent::DirectX11TransformComponent()
		:m_constantBuffer(&m_worldTransform, sizeof(m_worldTransform), ShaderBufferType::VERTEX)
	{
		m_Location = Vector3::Zero;
		m_Rotation = Vector3::Zero;
		m_Scale = Vector3(1.0f, 1.0f, 1.0f);
	}

	DirectX11TransformComponent::~DirectX11TransformComponent()
	{
		m_constantBuffer.Unbind();
	}

	void DirectX11TransformComponent::Bind()
	{
		m_constantBuffer.Bind(WorldTransformSlot);
	}

	void DirectX11TransformComponent::SetScale(float x, float y, float z)
	{
		m_Scale.x = x;
		m_Scale.y = y;
		m_Scale.z = z;
		UpdateTransformMatrix();
	}

	void DirectX11TransformComponent::SetRotation(float pitch, float yaw, float roll)
	{
		m_Rotation.x = pitch;
		m_Rotation.y = yaw;
		m_Rotation.z = roll;
		UpdateTransformMatrix();
	}

	void DirectX11TransformComponent::SetLocation(float x, float y, float z)
	{
		m_Location.x = x;
		m_Location.y = y;
		m_Location.z = z;
		UpdateTransformMatrix();
	}

	Vector3 DirectX11TransformComponent::GetScale()
	{
		return m_Scale;
	}

	Vector3 DirectX11TransformComponent::GetRotation()
	{
		return m_Rotation;
	}

	Vector3 DirectX11TransformComponent::GetLocation()
	{
		return m_Location;
	}

	void DirectX11TransformComponent::UpdateTransformMatrix()
	{
		m_worldTransform.world = (Matrix::CreateScale(m_Scale) *
			Matrix::CreateRotationY(m_Rotation.y) *
			Matrix::CreateRotationX(m_Rotation.x) *
			Matrix::CreateRotationZ(m_Rotation.z) *
			Matrix::CreateTranslation(m_Location)).Transpose();

		m_constantBuffer.UpdateData(&m_worldTransform, sizeof(m_worldTransform));
	}
}