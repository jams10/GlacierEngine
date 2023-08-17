#include "pch.h"
#include "Texture.h"

#include "Glacier/Renderer/Renderer.h"
#include "Platform/DirectX/Texture/DirectX11Texture2D.h"

namespace Glacier
{
	std::shared_ptr<Texture2D> Texture2D::Create(const std::wstring& filePath)
	{
		switch (Renderer::GetAPI())
		{
		case GraphicsAPI::API::None:    GR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case GraphicsAPI::API::DirectX11:  return std::make_shared<DirectX11Texture2D>(filePath);
		}

		GR_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}