#include "pch.h"
#include "Material.h"

#include "Renderer.h"
#include "Platform/DirectX/Material/DirectX11Material.h"

namespace Glacier
{
	Material* Material::Create()
	{
		switch (Renderer::GetAPI())
		{
		case GraphicsAPI::API::None:    GR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case GraphicsAPI::API::DirectX11:  return new DirectX11Material();
		}

		GR_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}