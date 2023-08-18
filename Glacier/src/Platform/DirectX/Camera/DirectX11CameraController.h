#pragma once

#include "Glacier/Core/Core.h"
#include "Glacier/Renderer/Camera/CameraController.h"

#include "Platform/DirectX/Buffer/ConstantBufferData.h"

namespace Glacier
{
	class ShaderBuffer;

	class GLACIER_API DirectX11CameraController : public CameraController
	{
	public:
		DirectX11CameraController(float aspectRatio);
		~DirectX11CameraController();

		virtual void OnUpdate(float dt) override;
		virtual void OnEvent(Event& e) override;

	private:
		CameraTransformConstant m_CameraTransformConstant;
		std::shared_ptr<ShaderBuffer> m_CameraTransformBuffer;
	};
}