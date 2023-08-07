#include "pch.h"
#include "DirectX11Device.h"
#include "DirectX11GraphicsAPI.h"
#include "DirectX11RenderContext.h"

namespace Glacier
{
	void DirectX11GraphicsAPI::SetClearColor(const glm::vec4& color)
	{
		float clearColor[4] = { color.r, color.g, color.b,color.a };
		DirectX11RenderContext::GetInstance()->SetClearColor(clearColor);
	}

	void DirectX11GraphicsAPI::Clear()
	{
		DirectX11RenderContext::GetInstance()->ClearRenderTargetView();
		DirectX11RenderContext::GetInstance()->ClearDepthStencilView();
	}

	void DirectX11GraphicsAPI::BeginRenderFrame()
	{
		DirectX11RenderContext::GetInstance()->SetRenderTarget();
	}

	void DirectX11GraphicsAPI::DrawIndexed(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{		
		DirectX11Device::GetDeviceContext()->DrawIndexed(indexBuffer->GetCount(), 0, 0);
	}
}