#pragma once

#include "Glacier/Core.h"

#include <d3d11.h>
#include <wrl.h>
#include <exception>

namespace Glacier
{
	using Microsoft::WRL::ComPtr;

	class GLACIER_API DirectX11RenderContext
	{
	public:
		~DirectX11RenderContext();

		void Init();
		static DirectX11RenderContext* GetInstance() { return s_Instance; }

		void SetClearColor(float clearColor[4]);
		void ClearRenderTargetView();
		void ClearDepthStencilView();
		void SetViewport(UINT startX , UINT startY, UINT screenWidth, UINT screenHeight);
		void ResizeWindow(uint32 width, uint32 height);
		void SetRenderTarget();

	private:
		DirectX11RenderContext() = default;

		void CreateBackbufferViews();
		void CreateDepthBuffer(UINT screenWidth, UINT screenHeight, ComPtr<ID3D11Texture2D>& depthTexture, ComPtr<ID3D11DepthStencilView>& depthTextureDSV);

	private:
		static DirectX11RenderContext* s_Instance;

	private:
		ComPtr<ID3D11RenderTargetView> m_BackbufferRTV = nullptr;
		ComPtr<ID3D11Texture2D> m_DepthStencilBuffer = nullptr;
		ComPtr<ID3D11DepthStencilView> m_DepthStencilView = nullptr;

		float m_ClearColor[4];
		UINT m_WholeScreenWidth;
		UINT m_WholeScreenHeight;
		D3D11_VIEWPORT m_ScreenViewport;
	};
}