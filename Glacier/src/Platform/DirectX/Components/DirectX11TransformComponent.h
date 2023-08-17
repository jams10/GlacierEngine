#pragma once

#include "Glacier/Components/TransformComponent.h"
#include "Platform/DirectX/Buffer/ConstantBufferData.h"
#include "Platform/DirectX/Buffer/DirectX11ConstantBuffer.h"

#include "SimpleMath.h"

namespace Glacier
{
	using DirectX::SimpleMath::Vector3;
	using DirectX::SimpleMath::Matrix;

	class GLACIER_API DirectX11TransformComponent : public TransformComponent
	{
	public:
		DirectX11TransformComponent();
		~DirectX11TransformComponent();

		virtual void Bind() override;
		virtual void SetScale(float x, float y, float z) override;
		virtual void SetRotation(float pitch, float roll, float yaw) override;
		virtual void SetLocation(float x, float y, float z) override;

		virtual Vector3 GetScale() override;
		virtual Vector3 GetRotation() override;
		virtual Vector3 GetLocation() override;

	private:
		
		void UpdateTransformMatrix();

		Vector3 m_Location;
		Vector3 m_Rotation;
		Vector3 m_Scale;
		WorldTransformConstant m_worldTransform;
		DirectX11ConstantBuffer m_constantBuffer;
	};
}