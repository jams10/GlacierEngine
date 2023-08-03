#pragma once

#include "Glacier/Renderer/RenderAPI.h"

namespace Glacier 
{
	class DirectX11RenderAPI : public RenderAPI
	{
	public:
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void BeginRenderFrame() override;

		virtual void DrawIndexed(const std::shared_ptr<IndexBuffer>& indexBuffer) override;
	};


}