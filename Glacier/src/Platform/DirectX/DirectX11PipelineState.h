#pragma once

#include "Glacier/Core/Core.h"

#include <d3d11.h>
#include <wrl.h>
#include <exception>

#include "Glacier/Renderer/RenderPipelineState.h"
#include "Glacier/Renderer/Shading/Shader.h"
#include "Glacier/Renderer/VertexLayout.h"

namespace Glacier
{
    using Microsoft::WRL::ComPtr;

	class GLACIER_API DirectX11PipelineState : public RenderPipelineState
	{
    public:
        DirectX11PipelineState();
        ~DirectX11PipelineState();
        void operator=(const DirectX11PipelineState& ps);

        virtual void Bind() override;
        virtual void UnBind() override;

        virtual std::shared_ptr<VertexLayout> GetVertexLayout() override;

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