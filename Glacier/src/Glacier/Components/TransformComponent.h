#pragma once

#include "Glacier/Core/Core.h"
#include "Glacier/Renderer/ConstantBufferData.h"
#include "BaseComponent.h"

#include "SimpleMath.h"

namespace Glacier
{
	class ShaderBuffer;

	using DirectX::SimpleMath::Vector3;

	class GLACIER_API TransformComponent : public BaseComponent
	{
	public:
		TransformComponent();
		~TransformComponent();

		virtual void Bind() override;
		void SetScale(float x, float y, float z);
		void SetRotation(float pitch, float yaw, float roll);
		void SetLocation(float x, float y, float z);

		Vector3 GetScale() const;
		Vector3 GetRotation() const;
		Vector3 GetLocation() const;

	private:

		void UpdateTransformMatrix();

		Vector3 m_Location;
		Vector3 m_Rotation;
		Vector3 m_Scale;
		WorldTransformConstant m_worldTransform;
		std::unique_ptr<ShaderBuffer> m_ConstantBuffer;
	};
}