#include "pch.h"
#include "DirectX11Device.h"
#include "DirectX11GraphicsAPI.h"
#include "DirectX11RenderContext.h"

namespace Glacier
{
	void DirectX11GraphicsAPI::SetClearColor(float colors[4])
	{
		DirectX11RenderContext::GetInstance()->SetClearColor(colors);
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