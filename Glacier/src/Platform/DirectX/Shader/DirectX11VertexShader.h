#pragma once

#include "Glacier/Renderer/Shading/Shader.h"

#include <d3d11.h>
#include <wrl.h>

namespace Glacier
{
	using Microsoft::WRL::ComPtr;

	class GLACIER_API DirectX11VertexShader : public VertexShader
	{
	public:
		DirectX11VertexShader(const std::wstring& shaderFilePath);
		virtual ~DirectX11VertexShader();

		virtual void Bind() const;
		virtual void Unbind() const;

		ComPtr<ID3DBlob> GetShaderBlob() const { return m_shaderBlob; }
	private:
		void CheckShaderCompile(HRESULT hr, ID3DBlob* errorBlob);

		ComPtr<ID3DBlob> m_shaderBlob;
		ComPtr<ID3D11VertexShader> m_shader;
	};
}