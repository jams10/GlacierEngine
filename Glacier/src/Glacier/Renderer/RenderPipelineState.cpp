#include "pch.h"
#include "RenderPipelineState.h"

#include "Renderer.h"
#include "Platform/DirectX/DirectX11PipelineState.h"

namespace Glacier
{
	RenderPipelineState* RenderPipelineState::Create()
	{
		switch (Renderer::GetAPI())
		{
		case GraphicsAPI::API::None:    GR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case GraphicsAPI::API::DirectX11:  return new DirectX11PipelineState();
		}

		GR_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}