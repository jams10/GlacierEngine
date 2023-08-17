#include "pch.h"
#include "TransformComponent.h"

#include "Glacier/Renderer/Renderer.h"
#include "Platform/DirectX/Components/DirectX11TransformComponent.h"

namespace Glacier
{
	TransformComponent* TransformComponent::Create()
	{
		switch (Renderer::GetAPI())
		{
		case GraphicsAPI::API::None:    GR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case GraphicsAPI::API::DirectX11:  return new DirectX11TransformComponent();
		}

		GR_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	} 
}