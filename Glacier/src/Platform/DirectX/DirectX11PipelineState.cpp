#include "pch.h"
#include "DirectX11PipelineState.h"

#include "DirectX11Common.h"
#include "DirectX11Device.h"

namespace Glacier
{
    void DirectX11PipelineState::operator=(const DirectX11PipelineState& ps)
    {
        m_VertexShader = ps.m_VertexShader;
        m_PixelShader = ps.m_PixelShader;
        m_InputLayout = ps.m_InputLayout;
        m_BlendState = ps.m_BlendState;
        m_DepthStencilState = ps.m_DepthStencilState;
        m_RasterizerState = ps.m_RasterizerState;
        m_PrimitiveTopology = ps.m_PrimitiveTopology;
    }

    void DirectX11PipelineState::Bind()
    {
        m_VertexShader->Bind();
        m_PixelShader->Bind();
        m_InputLayout->Bind();
        DirectX11Device::GetDeviceContext()->OMSetDepthStencilState(m_DepthStencilState.Get(), 0);
        DirectX11Device::GetDeviceContext()->RSSetState(m_RasterizerState.Get());
        DirectX11Device::GetDeviceContext()->IASetPrimitiveTopology(m_PrimitiveTopology);
        DirectX11Device::GetDeviceContext()->VSSetSamplers(0, UINT(Glacier::SamplerStates.size()), Glacier::SamplerStates.data());
        DirectX11Device::GetDeviceContext()->PSSetSamplers(0, UINT(Glacier::SamplerStates.size()), Glacier::SamplerStates.data());
    }

    void DirectX11PipelineState::UnBind()
    {
        m_VertexShader->Unbind();
        m_PixelShader->Unbind();
        m_InputLayout->Unbind();
        DirectX11Device::GetDeviceContext()->OMSetDepthStencilState(nullptr, 0);
        DirectX11Device::GetDeviceContext()->RSSetState(nullptr);
    }
}