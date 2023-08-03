#include "pch.h"
#include "DirectX11InputLayout.h"
#include "DirectX11VertexShader.h"
#include "DirectX11System.h"

#include <d3d11shader.h>
#include <d3dcompiler.inl>

namespace Glacier
{
	DirectX11InputLayout::DirectX11InputLayout(VertexShader* vertexShdaer)
	{
		CreateInputLayoutFromVertexShader(vertexShdaer);
	}

	DirectX11InputLayout::~DirectX11InputLayout()
	{
		m_InputLayout = nullptr;
	}

	void DirectX11InputLayout::Bind() const
	{
		DirectX11System::GetInstance()->GetDirectX11DeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		DirectX11System::GetInstance()->GetDirectX11DeviceContext()->IASetInputLayout(m_InputLayout.Get());
	}

	void DirectX11InputLayout::Unbind() const
	{
		DirectX11System::GetInstance()->GetDirectX11DeviceContext()->IASetInputLayout(nullptr);
	}

	void DirectX11InputLayout::CreateInputLayoutFromVertexShader(VertexShader* vertexShdaer)
	{
		// Code from Sentinel engine : https://github.com/CybernetHacker14/Sentinel

		std::unordered_map<DXGI_FORMAT, uint32> ShaderDataTypeSizeMap = {
			{DXGI_FORMAT_R32_FLOAT,          4},
			{DXGI_FORMAT_R32_UINT,           4},
			{DXGI_FORMAT_R32_SINT,           4},
			{DXGI_FORMAT_R32G32_FLOAT,       8},
			{DXGI_FORMAT_R32G32_UINT,        8},
			{DXGI_FORMAT_R32G32_SINT,        8},
			{DXGI_FORMAT_R32G32B32_FLOAT,   12},
			{DXGI_FORMAT_R32G32B32_UINT,    12},
			{DXGI_FORMAT_R32G32B32_SINT,    12},
			{DXGI_FORMAT_R32G32B32A32_FLOAT,16},
			{DXGI_FORMAT_R32G32B32A32_UINT, 16},
			{DXGI_FORMAT_R32G32B32A32_SINT, 16}
		};

		ID3DBlob* vertexShaderBinary = reinterpret_cast<DirectX11VertexShader*>(vertexShdaer)->GetShaderBlob().Get();

		ID3D11ShaderReflection* vertexShaderReflection = nullptr;
		if (FAILED(D3DReflect(vertexShaderBinary->GetBufferPointer(), vertexShaderBinary->GetBufferSize(),
			IID_ID3D11ShaderReflection, (void**)&vertexShaderReflection)))
		{
			GR_CORE_ASSERT(false, "Cannot reflect DirectX11 Vertex Shader!")
		}

		D3D11_SHADER_DESC shaderDescription;
		vertexShaderReflection->GetDesc(&shaderDescription);

		m_Stride = 0;

		std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDescriptions;
		for (uint16 i = 0; i < shaderDescription.InputParameters; i++)
		{
			D3D11_SIGNATURE_PARAMETER_DESC paramDescription;
			vertexShaderReflection->GetInputParameterDesc(i, &paramDescription);

			D3D11_INPUT_ELEMENT_DESC elementDescription;
			elementDescription.SemanticName = paramDescription.SemanticName;
			elementDescription.SemanticIndex = paramDescription.SemanticIndex;
			elementDescription.InputSlot = 0;
			elementDescription.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
			elementDescription.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			elementDescription.InstanceDataStepRate = 0;

			if (paramDescription.Mask == 1)
			{
				if (paramDescription.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
					elementDescription.Format = DXGI_FORMAT_R32_FLOAT;
				else if (paramDescription.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
					elementDescription.Format = DXGI_FORMAT_R32_UINT;
				else if (paramDescription.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
					elementDescription.Format = DXGI_FORMAT_R32_SINT;
			}
			else if (paramDescription.Mask <= 3)
			{
				if (paramDescription.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
					elementDescription.Format = DXGI_FORMAT_R32G32_FLOAT;
				else if (paramDescription.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
					elementDescription.Format = DXGI_FORMAT_R32G32_UINT;
				else if (paramDescription.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
					elementDescription.Format = DXGI_FORMAT_R32G32_SINT;
			}
			else if (paramDescription.Mask <= 7)
			{
				if (paramDescription.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
					elementDescription.Format = DXGI_FORMAT_R32G32B32_FLOAT;
				else if (paramDescription.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
					elementDescription.Format = DXGI_FORMAT_R32G32B32_UINT;
				else if (paramDescription.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
					elementDescription.Format = DXGI_FORMAT_R32G32B32_SINT;
			}
			else if (paramDescription.Mask <= 15)
			{
				if (paramDescription.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
					elementDescription.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
				else if (paramDescription.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
					elementDescription.Format = DXGI_FORMAT_R32G32B32A32_UINT;
				else if (paramDescription.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
					elementDescription.Format = DXGI_FORMAT_R32G32B32A32_SINT;
			}

			inputLayoutDescriptions.emplace_back(elementDescription);

			m_Stride += ShaderDataTypeSizeMap.at(elementDescription.Format);
		}

		DirectX11System::GetInstance()->GetDirectX11Device()->CreateInputLayout(
			&inputLayoutDescriptions[0], static_cast<uint32>(inputLayoutDescriptions.size()),
			vertexShaderBinary->GetBufferPointer(), vertexShaderBinary->GetBufferSize(), &m_InputLayout);

		vertexShaderReflection->Release();
	}


}