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
	extern ComPtr<ID3D11RasterizerState> rasterizerState_SolidCW;     // CW = �ð� ���� winding.
	extern ComPtr<ID3D11RasterizerState> rasterizerState_CullNone;    // D3D11_CULL_NONE ��带 ����ϴ� �����Ͷ�����.
	extern ComPtr<ID3D11RasterizerState> rasterizerState_WireCW;      // ���̾� ������ ��� �����Ͷ�����.
	extern ComPtr<ID3D11RasterizerState> rasterizerState_ImageFilter; // �̹��� ���Ϳ� �����Ͷ�����. ���� ���۸� ������� ����.

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

	// ���������� InitCommonStates()���� ���
	void InitSamplers();
	void InitRasterizerStates();
	void InitDepthStencilStates();
	void InitShaders();
	void InitPipelineStates();

}