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

		// ���̴��� �������� �̸��� "main"�� �Լ��� ����
		// D3D_COMPILE_STANDARD_FILE_INCLUDE �߰�: ���̴����� include ��� �����ϵ��� �Ͽ� hlsli������ ���� ��ų �� ����.
		// ���̴����� ��� ���� ��� �� �÷��׸� �Ʒ��� ���� ���������� ������ shader file not found ������ �߻� ����.
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
			// ���̴� ������ ���� ���.
			if ((hr & D3D11_ERROR_FILE_NOT_FOUND) != 0)
			{
				GR_CORE_ERROR("Shader Compile Error! : Shader file not found.\n");
			}

			// ���� �޽����� ������ ���.
			if (errorBlob)
			{
				GR_CORE_ERROR("Shader Compile Error! : Shader compile error\n");
				GR_CORE_ERROR("{0}\n", (char*)errorBlob->GetBufferPointer());
			}
		}
	}
}