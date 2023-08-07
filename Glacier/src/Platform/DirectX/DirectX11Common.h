#pragma once

#include "Glacier/Core.h"
#include "DirectX11PipelineState.h"

#include "Glacier/Renderer/Shader.h"
#include "Glacier/Renderer/VertexLayout.h"

#include <vector>

namespace Glacier
{
	// Samplers
	extern ComPtr<ID3D11SamplerState> samplerState_LinearWrap;
	extern ComPtr<ID3D11SamplerState> samplerState_LinearClamp;
	extern std::vector<ID3D11SamplerState*> samplerStates;

	// Rasterizer States
	extern ComPtr<ID3D11RasterizerState> rasterizerState_SolidCW;     // CW = 시계 방향 winding.
	extern ComPtr<ID3D11RasterizerState> rasterizerState_CullNone;    // D3D11_CULL_NONE 모드를 사용하는 래스터라이저.
	extern ComPtr<ID3D11RasterizerState> rasterizerState_WireCW;      // 와이어 프레임 모드 래스터라이저.
	extern ComPtr<ID3D11RasterizerState> rasterizerState_ImageFilter; // 이미지 필터용 래스터라이저. 깊이 버퍼를 사용하지 않음.

	// Depth Stencil States
	extern ComPtr<ID3D11DepthStencilState> depthStencilState_Default;

	// Shaders
	extern std::shared_ptr<VertexShader> vertexShader_Color;
	extern std::shared_ptr<FragmentShader> pixelShader_Color;

	// Input Layouts
	extern std::shared_ptr<VertexLayout> inputLayout_Color;

	// Pipeline States
	extern DirectX11PipelineState vertexColorPipelineState;
	extern DirectX11PipelineState vertexColorWirePipelineState;

	void InitCommonStates();

	// 내부적으로 InitCommonStates()에서 사용
	void InitSamplers();
	void InitRasterizerStates();
	void InitDepthStencilStates();
	void InitShaders();
	void InitPipelineStates();

}