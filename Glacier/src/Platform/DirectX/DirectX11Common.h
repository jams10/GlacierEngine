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
	extern ComPtr<ID3D11RasterizerState> RasterizerState_SolidCW;     // CW = �ð� ���� winding.
	extern ComPtr<ID3D11RasterizerState> RasterizerState_CullNone;    // D3D11_CULL_NONE ��带 ����ϴ� �����Ͷ�����.
	extern ComPtr<ID3D11RasterizerState> RasterizerState_WireCW;      // ���̾� ������ ��� �����Ͷ�����.
	extern ComPtr<ID3D11RasterizerState> RasterizerState_ImageFilter; // �̹��� ���Ϳ� �����Ͷ�����. ���� ���۸� ������� ����.

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

	// ���������� InitCommonStates()���� ���
	void InitSamplers();
	void InitRasterizerStates();
	void InitDepthStencilStates();
	void InitShaders();
	void InitPipelineStates();

}