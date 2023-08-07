#include "pch.h"
#include "DirectX11VertexShader.h"
#include "Platform/DirectX/DirectX11Device.h"

#include <d3dcompiler.h>

namespace Glacier
{
	DirectX11VertexShader::DirectX11VertexShader(const std::wstring& shaderFilePath)
	{
		ComPtr<ID3DBlob> errorBlob;

		UINT compileFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
		compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

		// 쉐이더의 시작점의 이름이 "main"인 함수로 지정
		// D3D_COMPILE_STANDARD_FILE_INCLUDE 추가: 쉐이더에서 include 사용 가능하도록 하여 hlsli파일을 포함 시킬 수 있음.
		// 쉐이더에서 헤더 파일 사용 시 플래그를 아래와 같이 지정해주지 않으면 shader file not found 에러가 발생 했음.
		HRESULT hr = D3DCompileFromFile(
			shaderFilePath.c_str(), 0, D3D_COMPILE_STANDARD_FILE_INCLUDE, "main",
			"vs_5_0", compileFlags, 0, &m_shaderBlob, &errorBlob);

		CheckShaderCompile(hr, errorBlob.Get());

		DirectX11Device::GetDevice()->CreateVertexShader(
			m_shaderBlob->GetBufferPointer(), m_shaderBlob->GetBufferSize(), NULL, &m_shader
		);
	}

	DirectX11VertexShader::~DirectX11VertexShader()
	{
		m_shader = nullptr;
	}

	void DirectX11VertexShader::Bind() const
	{
		DirectX11Device::GetDeviceContext()->VSSetShader(m_shader.Get(), 0, 0);
	}

	void DirectX11VertexShader::Unbind() const
	{
		DirectX11Device::GetDeviceContext()->VSSetShader(nullptr, 0, 0);
	}

	void DirectX11VertexShader::CheckShaderCompile(HRESULT hr, ID3DBlob* errorBlob)
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