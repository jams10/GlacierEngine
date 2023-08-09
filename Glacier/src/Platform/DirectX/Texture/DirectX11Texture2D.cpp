#include "pch.h"
#include "DirectX11Texture2D.h"

#include "Glacier/Utils/StringEncode.h"
#include "Platform/DirectX/DirectX11Device.h"
#include "stb_image.h"

namespace Glacier
{
	DirectX11Texture2D::DirectX11Texture2D(const std::wstring& filePath)
	{
		int width, height, channels;
		std::string path = WideToMultiU8(filePath);

		unsigned char* img = stbi_load(path.c_str(), &width, &height, &channels, 0);
		if (img == nullptr)
		{
			std::cout << "\n\nCan't load the texture file! : " << path << '\n\n';
			return;
		}
		//assert(channels == 4);

		// 4채널로 만들어서 복사
		std::vector<uint8> image;
		image.resize(width * height * 4);
		for (size_t i = 0; i < width * height; i++)
		{
			for (size_t c = 0; c < 3; c++)
			{
				image[4 * i + c] = img[i * channels + c];
			}
			image[4 * i + 3] = 255;
		}

		m_Width = width;
		m_Height = height;

		// 텍스쳐 생성.
		D3D11_TEXTURE2D_DESC txtDesc = {};
		txtDesc.Width = width;
		txtDesc.Height = height;
		txtDesc.MipLevels = txtDesc.ArraySize = 1;
		txtDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		txtDesc.SampleDesc.Count = 1;
		txtDesc.Usage = D3D11_USAGE_IMMUTABLE;
		txtDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

		// 실제로 들어갈 데이터 채워주기.
		D3D11_SUBRESOURCE_DATA initData;
		initData.pSysMem = image.data();
		initData.SysMemPitch = txtDesc.Width * sizeof(uint8_t) * 4;
		// initData.SysMemSlicePitch = 0;

		DirectX11Device::GetDevice()->CreateTexture2D(&txtDesc, &initData, m_GpuTexture.GetAddressOf());
		DirectX11Device::GetDevice()->CreateShaderResourceView(m_GpuTexture.Get(), nullptr, m_TexureSRV.GetAddressOf());
	}

	DirectX11Texture2D::~DirectX11Texture2D()
	{
		m_TexureSRV = nullptr;
		m_GpuTexture = nullptr;
	}

	uint32 DirectX11Texture2D::GetWidth()
	{
		return m_Width;
	}

	uint32 DirectX11Texture2D::GetHeight()
	{
		return m_Height;
	}

	void DirectX11Texture2D::Bind(uint32 slot) const
	{
		DirectX11Device::GetDeviceContext()->PSSetShaderResources(slot, 1, m_TexureSRV.GetAddressOf());
	}
}