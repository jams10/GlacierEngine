#include "pch.h"
#include "VertexLayout.h"

#include "Renderer.h"
#include "Platform/DirectX/DirectX11InputLayout.h"

namespace Glacier
{
	VertexLayout* VertexLayout::Create()
	{
		return nullptr;
	}

	VertexLayout* VertexLayout::Create(VertexShader* vertexShader)
	{
		switch (Renderer::GetAPI())
		{
			case GraphicsAPI::API::None:    GR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case GraphicsAPI::API::DirectX11:  return new DirectX11InputLayout(vertexShader);
		}

		GR_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}