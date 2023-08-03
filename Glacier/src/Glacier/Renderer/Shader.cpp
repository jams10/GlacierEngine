#include "pch.h"
#include "Shader.h"

#include "Glacier/Renderer/Renderer.h"
#include "Platform/DirectX/DirectX11VertexShader.h"
#include "Platform/DirectX/DirectX11PixelShader.h"

namespace Glacier
{
	VertexShader* VertexShader::Create(const std::wstring& shaderFilePath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:    GR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::DirectX11:  return new DirectX11VertexShader(shaderFilePath);
		}

		GR_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	FragmentShader* FragmentShader::Create(const std::wstring& shaderFilePath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:    GR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::DirectX11:  return new DirectX11PixelShader(shaderFilePath);
		}

		GR_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}