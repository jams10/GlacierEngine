#pragma once

#include "Glacier/Core/Core.h"
#include "Glacier/Renderer/Shading/Texture.h"

#include <d3d11.h>
#include <wrl.h>

namespace Glacier
{
	using Microsoft::WRL::ComPtr;

	class GLACIER_API DirectX11Texture2D : public Texture2D
	{
	public:
		DirectX11Texture2D(const std::wstring& filePath);
		virtual ~DirectX11Texture2D();

		virtual uint32 GetWidth() override;
		virtual uint32 GetHeight() override;

		virtual void Bind(uint32 slot) const override;

	private:
		ComPtr<ID3D11Texture2D> m_GpuTexture = nullptr;
		ComPtr<ID3D11ShaderResourceView> m_TexureSRV = nullptr;
		uint32 m_Width;
		uint32 m_Height;
	};
}