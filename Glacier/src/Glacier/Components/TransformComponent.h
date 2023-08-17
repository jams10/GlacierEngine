#pragma once

#include "Glacier/Core/Core.h"

#include "SimpleMath.h"

namespace Glacier
{
	using DirectX::SimpleMath::Vector3;

	class GLACIER_API TransformComponent
	{
	public:
		~TransformComponent() {}

		virtual void Bind() = 0;
		virtual void SetScale(float x, float y, float z) = 0;
		virtual void SetRotation(float pitch, float roll, float yaw) = 0;
		virtual void SetLocation(float x, float y, float z) = 0;

		virtual Vector3 GetScale() = 0;
		virtual Vector3 GetRotation() = 0;
		virtual Vector3 GetLocation() = 0;

		static TransformComponent* Create();
	};
}