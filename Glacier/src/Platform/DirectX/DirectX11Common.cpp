#include "pch.h"
#include "DirectX11Common.h"
#include "DirectX11Device.h"

#include <d3dcompiler.h>

namespace Glacier
{
	// Samplers
	ComPtr<ID3D11SamplerState> samplerState_LinearWrap;
	ComPtr<ID3D11SamplerState> samplerState_LinearClamp;
	std::vector<ID3D11SamplerState*> samplerStates;

	// Rasterizer States
	ComPtr<ID3D11RasterizerState> rasterizerState_SolidCW;
	ComPtr<ID3D11RasterizerState> rasterizerState_CullNone;
	ComPtr<ID3D11RasterizerState> rasterizerState_WireCW;
	ComPtr<ID3D11RasterizerState> rasterizerState_ImageFilter;

	// Depth Stencil States
	ComPtr<ID3D11DepthStencilState> depthStencilState_Default;

	// Shaders
	std::shared_ptr<VertexShader> vertexShader_Color;
	std::shared_ptr<FragmentShader> pixelShader_Color;

	// Input Layouts
	std::shared_ptr<VertexLayout> inputLayout_Color;

	// Pipeline States
	DirectX11PipelineState vertexColorPipelineState;
	DirectX11PipelineState vertexColorWirePipelineState;

	void Glacier::InitCommonStates()
	{
		InitShaders();
		InitSamplers();
		InitRasterizerStates();
		InitDepthStencilStates();
		InitPipelineStates();
	}

	void Glacier::InitSamplers()
	{
		D3D11_SAMPLER_DESC sampDesc;
		ZeroMemory(&sampDesc, sizeof(sampDesc));
		sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		sampDesc.MinLOD = 0;
		sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
		DirectX11Device::GetDevice()->CreateSamplerState(&sampDesc, samplerState_LinearWrap.GetAddressOf());
		sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		DirectX11Device::GetDevice()->CreateSamplerState(&sampDesc, samplerState_LinearClamp.GetAddressOf());

		// 샘플러 순서가 "Common.hlsli"에서와 일관성 있어야 함
		samplerStates.push_back(samplerState_LinearWrap.Get());
		samplerStates.push_back(samplerState_LinearClamp.Get());
	}

	void Glacier::InitRasterizerStates()
	{
		// Rasterizer States
		D3D11_RASTERIZER_DESC rastDesc;
		ZeroMemory(&rastDesc, sizeof(D3D11_RASTERIZER_DESC));
		rastDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rastDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
		rastDesc.FrontCounterClockwise = false;
		rastDesc.DepthClipEnable = true;
		rastDesc.MultisampleEnable = true;
		THROWFAILED(DirectX11Device::GetDevice()->CreateRasterizerState(&rastDesc, rasterizerState_SolidCW.GetAddressOf()));

		rastDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		THROWFAILED(DirectX11Device::GetDevice()->CreateRasterizerState(&rastDesc, rasterizerState_CullNone.GetAddressOf()));

		rastDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
		THROWFAILED(DirectX11Device::GetDevice()->CreateRasterizerState(&rastDesc, rasterizerState_WireCW.GetAddressOf()));

		rastDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rastDesc.DepthClipEnable = false;
		THROWFAILED(DirectX11Device::GetDevice()->CreateRasterizerState(&rastDesc, rasterizerState_ImageFilter.GetAddressOf()));
	}

	void Glacier::InitDepthStencilStates()
	{
		// Depth Stencil State(깊이 값을 어떻게 비교할 것인가를 결정)를 생성.
		D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
		ZeroMemory(&depthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
		depthStencilDesc.DepthEnable = true;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
		THROWFAILED(DirectX11Device::GetDevice()->CreateDepthStencilState(&depthStencilDesc, depthStencilState_Default.GetAddressOf()));
	}

	void Glacier::InitShaders()
	{
		vertexShader_Color.reset(VertexShader::Create(L"../Glacier/resources/shaders/VertexColorVS.hlsl"));
		inputLayout_Color.reset(VertexLayout::Create(vertexShader_Color.get()));
		pixelShader_Color.reset(FragmentShader::Create(L"../Glacier/resources/shaders/VertexColorPS.hlsl"));
	}

	void Glacier::InitPipelineStates()
	{
		vertexColorPipelineState.m_VertexShader = vertexShader_Color;
		vertexColorPipelineState.m_PixelShader = pixelShader_Color;
		vertexColorPipelineState.m_InputLayout = inputLayout_Color;
		vertexColorPipelineState.m_DepthStencilState = depthStencilState_Default;
		vertexColorPipelineState.m_RasterizerState = rasterizerState_SolidCW;
		vertexColorPipelineState.m_PrimitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

		vertexColorWirePipelineState = vertexColorPipelineState;
		vertexColorWirePipelineState.m_RasterizerState = rasterizerState_WireCW;

		GR_CORE_WARN("DirectX11 Pipeline states have initialized successfully!");
	}
}