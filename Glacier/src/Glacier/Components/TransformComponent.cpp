#include "pch.h"
#include "TransformComponent.h"
#include "Glacier/Renderer/Buffer.h"

namespace Glacier
{
	TransformComponent::TransformComponent()
	{
		m_ConstantBuffer.reset(Glacier::ShaderBuffer::Create(&m_worldTransform, sizeof(m_worldTransform), ShaderBufferType::VERTEX));
	}

	TransformComponent::~TransformComponent()
	{
		m_ConstantBuffer = nullptr;
	}

	void TransformComponent::Bind()
	{
		if (m_ConstantBuffer)
		{
			m_ConstantBuffer->Bind(WorldTransformSlot);
		}
	}

	void TransformComponent::SetScale(float x, float y, float z)
	{
		m_Scale.x = x;
		m_Scale.y = y;
		m_Scale.z = z;
		UpdateTransformMatrix();
	}

	void TransformComponent::SetRotation(float pitch, float yaw, float roll)
	{
		m_Rotation.x = pitch;
		m_Rotation.y = yaw;
		m_Rotation.z = roll;
		UpdateTransformMatrix();
	}

	void TransformComponent::SetLocation(float x, float y, float z)
	{
		m_Location.x = x;
		m_Location.y = y;
		m_Location.z = z;
		UpdateTransformMatrix();
	}

	Vector3 TransformComponent::GetScale() const
	{
		return m_Scale;
	}

	Vector3 TransformComponent::GetRotation() const
	{
		return m_Rotation;
	}

	Vector3 TransformComponent::GetLocation() const
	{
		return m_Location;
	}

	void TransformComponent::UpdateTransformMatrix()
	{
		m_worldTransform.world = (Matrix::CreateScale(m_Scale) *
			Matrix::CreateRotationY(m_Rotation.y) *
			Matrix::CreateRotationX(m_Rotation.x) *
			Matrix::CreateRotationZ(m_Rotation.z) *
			Matrix::CreateTranslation(m_Location)).Transpose();

		m_ConstantBuffer->UpdateData(&m_worldTransform, sizeof(m_worldTransform));
	}

}