#pragma once

#include "Glacier/Renderer/GraphicsAPI.h"

namespace Glacier 
{
	class GLACIER_API DirectX11GraphicsAPI : public GraphicsAPI
	{
	public:
		virtual void SetClearColor(float colors[4]) override;
		virtual void Clear() override;

		virtual void BeginRenderFrame() override;

		virtual void DrawIndexed(const std::shared_ptr<IndexBuffer>& indexBuffer) override;
	};
}