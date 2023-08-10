#include "pch.h"
#include "DirectX11Device.h"
#include "DirectX11GraphicsAPI.h"
#include "DirectX11RenderContext.h"

namespace Glacier
{
	void DirectX11GraphicsAPI::ResizeWindow(uint32 width, uint32 height)
	{
		DirectX11RenderContext::GetInstance()->ResizeWindow(width, height);
	}

	void DirectX11GraphicsAPI::SetViewport(uint32 x, uint32 y, uint32 width, uint32 height)
	{
		DirectX11RenderContext::GetInstance()->SetViewport((UINT)x, (UINT)y, (UINT)width, (UINT)height);
	}

	void DirectX11GraphicsAPI::SetClearColor(float colors[4])
	{
		DirectX11RenderContext::GetInstance()->SetClearColor(colors);
	}

	void DirectX11GraphicsAPI::Clear()
	{
		DirectX11RenderContext::GetInstance()->ClearRenderTargetView();
		DirectX11RenderContext::GetInstance()->ClearDepthStencilView();
	}

	void DirectX11GraphicsAPI::SetRenderTarget()
	{
		DirectX11RenderContext::GetInstance()->SetRenderTarget();
	}

	void DirectX11GraphicsAPI::DrawIndexed(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{		
		DirectX11Device::GetDeviceContext()->DrawIndexed(indexBuffer->GetCount(), 0, 0);
	}
}