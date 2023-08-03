#include "pch.h"
#include "DirectX11RenderAPI.h"
#include "DirectX11System.h"


namespace Glacier
{
	void DirectX11RenderAPI::SetClearColor(const glm::vec4& color)
	{
		float clearColor[4] = { color.r, color.g, color.b,color.a };
		DirectX11System::GetInstance()->SetClearColor(clearColor);
	}

	void DirectX11RenderAPI::Clear()
	{
		DirectX11System::GetInstance()->ClearRenderTargetView();
		DirectX11System::GetInstance()->ClearDepthStencilView();
	}

	void DirectX11RenderAPI::BeginRenderFrame()
	{
		DirectX11System::GetInstance()->BeginFrame();
	}

	void DirectX11RenderAPI::DrawIndexed(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		DirectX11System::GetInstance()->GetDirectX11DeviceContext()->DrawIndexed(indexBuffer->GetCount(), 0, 0);
	}
}