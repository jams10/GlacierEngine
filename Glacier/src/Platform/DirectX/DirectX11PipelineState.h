#pragma once

#include "Glacier/Core.h"

#include <d3d11.h>
#include <wrl.h>
#include <exception>

#include "Glacier/Renderer/Shader.h"
#include "Glacier/Renderer/VertexLayout.h"

namespace Glacier
{
    using Microsoft::WRL::ComPtr;

	class GLACIER_API DirectX11PipelineState
	{
    public:
        void operator=(const DirectX11PipelineState& ps);

        void Bind();
        void UnBind();

    public:
        std::shared_ptr<VertexShader> m_VertexShader;
        std::shared_ptr<FragmentShader> m_PixelShader;
        std::shared_ptr<VertexLayout> m_InputLayout;

        ComPtr<ID3D11BlendState> m_BlendState;
        ComPtr<ID3D11DepthStencilState> m_DepthStencilState;
        ComPtr<ID3D11RasterizerState> m_RasterizerState;

        D3D11_PRIMITIVE_TOPOLOGY m_PrimitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
        int32 m_VertexStride;
	};
}

//// rasterizer state »ý¼º.
//D3D11_RASTERIZER_DESC rastDesc;
//ZeroMemory(&rastDesc, sizeof(D3D11_RASTERIZER_DESC));
//rastDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
//// rastDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
//rastDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
//rastDesc.FrontCounterClockwise = false;
//
//DirectX11Device::GetDevice()->CreateRasterizerState(&rastDesc, &m_RasterizerState);

	//	m_Context->OMSetDepthStencilState(m_DepthStencilState.Get(), 0);
	//	m_Context->RSSetState(m_RasterizerState.Get());