#include "pch.h"
#include "DirectX11PixelShader.h"
#include "Platform/DirectX/DirectX11Device.h"

#include <d3dcompiler.h>

namespace Glacier
{
	DirectX11PixelShader::DirectX11PixelShader(const std::wstring& shaderFilePath)
	{
		ComPtr<ID3DBlob> errorBlob;

		UINT compileFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
		compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

		HRESULT hr = D3DCompileFromFile(
			shaderFilePath.c_str(), 0, D3D_COMPILE_STANDARD_FILE_INCLUDE, "main",
			"ps_5_0", compileFlags, 0, &m_shaderBlob, &errorBlob);

		CheckShaderCompile(hr, errorBlob.Get());

		DirectX11Device::GetDevice()->CreatePixelShader(
			m_shaderBlob->GetBufferPointer(), m_shaderBlob->GetBufferSize(), NULL, &m_shader);
	}

	DirectX11PixelShader::~DirectX11PixelShader()
	{
		m_shader = nullptr;
	}

	void DirectX11PixelShader::Bind() const
	{
		DirectX11Device::GetDeviceContext()->PSSetShader(m_shader.Get(), 0, 0);
	}

	void DirectX11PixelShader::Unbind() const
	{
		DirectX11Device::GetDeviceContext()->PSSetShader(nullptr, 0, 0);
	}

	void DirectX11PixelShader::CheckShaderCompile(HRESULT hr, ID3DBlob* errorBlob)
	{
		if (FAILED(hr))
		{
			// 쉐이더 파일이 없을 경우.
			if ((hr & D3D11_ERROR_FILE_NOT_FOUND) != 0)
			{
				GR_CORE_ERROR("Shader Compile Error! : Shader file not found.\n");
			}

			// 에러 메시지가 있으면 출력.
			if (errorBlob)
			{
				GR_CORE_ERROR("Shader Compile Error! : Shader compile error\n");
				GR_CORE_ERROR("{0}\n", (char*)errorBlob->GetBufferPointer());
			}
		}
	}
}