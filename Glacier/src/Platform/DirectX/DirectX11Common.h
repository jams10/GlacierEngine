#pragma once

#include "Glacier/Core/Core.h"

#include "Glacier/Renderer/Shading/Shader.h"
#include "Glacier/Renderer/VertexLayout.h"
#include "Glacier/Renderer/RenderPipelineState.h"

#include <d3d11.h>
#include <wrl.h>

#include <vector>

namespace Glacier
{
	using Microsoft::WRL::ComPtr;

	// Samplers
	extern ComPtr<ID3D11SamplerState> SamplerState_LinearWrap;
	extern ComPtr<ID3D11SamplerState> SamplerState_LinearClamp;
	extern std::vector<ID3D11SamplerState*> SamplerStates;

	// Rasterizer States
	extern ComPtr<ID3D11RasterizerState> RasterizerState_SolidCW;     // CW = 시계 방향 winding.
	extern ComPtr<ID3D11RasterizerState> RasterizerState_CullNone;    // D3D11_CULL_NONE 모드를 사용하는 래스터라이저.
	extern ComPtr<ID3D11RasterizerState> RasterizerState_WireCW;      // 와이어 프레임 모드 래스터라이저.
	extern ComPtr<ID3D11RasterizerState> RasterizerState_ImageFilter; // 이미지 필터용 래스터라이저. 깊이 버퍼를 사용하지 않음.

	// Depth Stencil States
	extern ComPtr<ID3D11DepthStencilState> DepthStencilState_Default;

	// Shaders
	extern std::shared_ptr<VertexShader> VertexShader_Color;
	extern std::shared_ptr<FragmentShader> PixelShader_Color;
	extern std::shared_ptr<VertexShader> VertexShader_TextureSample;
	extern std::shared_ptr<FragmentShader> PixelShader_TextureSample;

	// Input Layouts
	extern std::shared_ptr<VertexLayout> InputLayout_Color;
	extern std::shared_ptr<VertexLayout> InputLayout_TextureSample;

	void InitCommonStates();

	// 내부적으로 InitCommonStates()에서 사용
	void InitSamplers();
	void InitRasterizerStates();
	void InitDepthStencilStates();
	void InitShaders();
	void InitPipelineStates();

}