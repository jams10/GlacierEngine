#pragma once

#include "Glacier/Renderer/GraphicsAPI.h"

namespace Glacier 
{
	class GLACIER_API DirectX11GraphicsAPI : public GraphicsAPI
	{
	public:
		virtual void ResizeWindow(uint32 width, uint32 height) override;
		virtual void SetViewport(uint32 x, uint32 y, uint32 width, uint32 height) override;
		//virtual void SetClearColor(float colors[4]) override;
		//virtual void Clear() override;
		virtual void ClearForRenderScene(float colors[4]) override;
		virtual void ClearForRenderUI(float colors[4]) override;

		virtual void SetSceneRenderTarget() override;
		virtual void SetUIRenderTarget() override;

		virtual void DrawIndexed(const std::shared_ptr<IndexBuffer>& indexBuffer) override;
		virtual void PrepareSceneRenderedTexture() override;
		virtual void* GetSceneRenderedTexture() override;
	};
}