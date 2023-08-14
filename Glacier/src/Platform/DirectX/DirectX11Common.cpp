#include "pch.h"
#include "DirectX11Common.h"
#include "DirectX11Device.h"

#include "DirectX11PipelineState.h"

#include <d3dcompiler.h>

namespace Glacier
{
	// Samplers
	ComPtr<ID3D11SamplerState> SamplerState_LinearWrap;
	ComPtr<ID3D11SamplerState> SamplerState_LinearClamp;
	std::vector<ID3D11SamplerState*> SamplerStates;

	// Rasterizer States
	ComPtr<ID3D11RasterizerState> RasterizerState_SolidCW;
	ComPtr<ID3D11RasterizerState> RasterizerState_CullNone;
	ComPtr<ID3D11RasterizerState> RasterizerState_WireCW;
	ComPtr<ID3D11RasterizerState> RasterizerState_ImageFilter;

	// Depth Stencil States
	ComPtr<ID3D11DepthStencilState> DepthStencilState_Default;

	// Shaders
	std::shared_ptr<VertexShader> VertexShader_Color;
	std::shared_ptr<FragmentShader> PixelShader_Color;
	std::shared_ptr<VertexShader> VertexShader_TextureSample;
	std::shared_ptr<FragmentShader> PixelShader_TextureSample;

	// Input Layouts
	std::shared_ptr<VertexLayout> InputLayout_Color;
	std::shared_ptr<VertexLayout> InputLayout_TextureSample;

	// Pipeline States
	std::unique_ptr<RenderPipelineState> VertexColorPipelineState;
	std::unique_ptr<RenderPipelineState> VertexColorWirePipelineState;
	std::unique_ptr<RenderPipelineState> TexureSamplingPipelineState;

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
		DirectX11Device::GetDevice()->CreateSamplerState(&sampDesc, SamplerState_LinearWrap.GetAddressOf());
		sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		DirectX11Device::GetDevice()->CreateSamplerState(&sampDesc, SamplerState_LinearClamp.GetAddressOf());

		// 샘플러 순서가 "Common.hlsli"에서와 일관성 있어야 함
		SamplerStates.push_back(SamplerState_LinearWrap.Get());
		SamplerStates.push_back(SamplerState_LinearClamp.Get());
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
		THROWFAILED(DirectX11Device::GetDevice()->CreateRasterizerState(&rastDesc, RasterizerState_SolidCW.GetAddressOf()));

		rastDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		THROWFAILED(DirectX11Device::GetDevice()->CreateRasterizerState(&rastDesc, RasterizerState_CullNone.GetAddressOf()));

		rastDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
		THROWFAILED(DirectX11Device::GetDevice()->CreateRasterizerState(&rastDesc, RasterizerState_WireCW.GetAddressOf()));

		rastDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rastDesc.DepthClipEnable = false;
		THROWFAILED(DirectX11Device::GetDevice()->CreateRasterizerState(&rastDesc, RasterizerState_ImageFilter.GetAddressOf()));
	}

	void Glacier::InitDepthStencilStates()
	{
		// Depth Stencil State(깊이 값을 어떻게 비교할 것인가를 결정)를 생성.
		D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
		ZeroMemory(&depthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
		depthStencilDesc.DepthEnable = true;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
		THROWFAILED(DirectX11Device::GetDevice()->CreateDepthStencilState(&depthStencilDesc, DepthStencilState_Default.GetAddressOf()));
	}

	void Glacier::InitShaders()
	{
		VertexShader_Color.reset(VertexShader::Create(L"../Glacier/resources/shaders/VertexColor_VS.hlsl"));
		InputLayout_Color.reset(VertexLayout::Create(VertexShader_Color.get()));
		PixelShader_Color.reset(FragmentShader::Create(L"../Glacier/resources/shaders/VertexColor_PS.hlsl"));

		VertexShader_TextureSample.reset(VertexShader::Create(L"../Glacier/resources/shaders/TextureSample_VS.hlsl"));
		InputLayout_TextureSample.reset(VertexLayout::Create(VertexShader_TextureSample.get()));
		PixelShader_TextureSample.reset(FragmentShader::Create(L"../Glacier/resources/shaders/TextureSample_PS.hlsl"));
	}

	void Glacier::InitPipelineStates()
	{
		DirectX11PipelineState* VertexColorPS = nullptr;
		VertexColorPipelineState.reset(Glacier::RenderPipelineState::Create());
		VertexColorPS = reinterpret_cast<DirectX11PipelineState*>(VertexColorPipelineState.get());

		VertexColorPS->m_VertexShader = VertexShader_Color;
		VertexColorPS->m_PixelShader = PixelShader_Color;
		VertexColorPS->m_InputLayout = InputLayout_Color;
		VertexColorPS->m_DepthStencilState = DepthStencilState_Default;
		VertexColorPS->m_RasterizerState = RasterizerState_SolidCW;
		VertexColorPS->m_PrimitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

		DirectX11PipelineState* VertexColorWirePS = nullptr;
		VertexColorWirePipelineState.reset(Glacier::RenderPipelineState::Create());
		VertexColorWirePS = reinterpret_cast<DirectX11PipelineState*>(VertexColorWirePipelineState.get());

		*VertexColorWirePS = *VertexColorPS;
		VertexColorWirePS->m_RasterizerState = RasterizerState_WireCW;

		DirectX11PipelineState* TextureSamplingPS = nullptr;
		TexureSamplingPipelineState.reset(Glacier::RenderPipelineState::Create());
		TextureSamplingPS = reinterpret_cast<DirectX11PipelineState*>(TexureSamplingPipelineState.get());

		*TextureSamplingPS = *VertexColorPS;
		TextureSamplingPS->m_VertexShader = VertexShader_TextureSample;
		TextureSamplingPS->m_InputLayout = InputLayout_TextureSample;
		TextureSamplingPS->m_PixelShader = PixelShader_TextureSample;

		GR_CORE_WARN("DirectX11 Pipeline states have initialized successfully!");
	}
}