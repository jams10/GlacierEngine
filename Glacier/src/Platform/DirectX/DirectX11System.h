#pragma once

#include "Glacier/Core.h"
#include "Platform/Windows/WindowsHeaders.h"

#include <d3d11.h>
#include <wrl.h>
#include <exception>

namespace Glacier
{
	using Microsoft::WRL::ComPtr;

#define THROWFAILED(x) ThrowIfFailed(x)

	inline void ThrowIfFailed(HRESULT hr)
	{
		if (FAILED(hr))
		{
			throw std::exception();
		}
	}

	class GLACIER_API DirectX11System {
	public:
		~DirectX11System();

		void Init(HWND hWnd);
		static DirectX11System* GetInstance();

		ComPtr<ID3D11Device> GetDirectX11Device() const { return m_Device; }
		ComPtr<IDXGISwapChain> GetDirectX11SwapChain() const { return m_Swapchain; }
		ComPtr<ID3D11DeviceContext> GetDirectX11DeviceContext() const { return m_Context; }
		ComPtr<ID3D11RenderTargetView> GetDirectX11RenderTargetView() const { return m_BackbufferRTV; }
		ComPtr<ID3D11RasterizerState> GetRasterizerState() const { return m_RasterizerState; }

		ComPtr<IDXGIDevice> GetDirectX11DXGIDevice() const { return m_DXGIDevice; }
		ComPtr<IDXGIAdapter> GetDirectX11Adapter() const { return m_Adapter; }
		DXGI_ADAPTER_DESC* GetDirectX11AdapterDescription() const { return m_AdapterDescription; }

		void BeginFrame();

	private:
		DirectX11System() = default;

		void CreateBackbufferViews();
		void SetViewport(UINT screenWidth, UINT screenHeight);
		void CreateDepthBuffer(UINT screenWidth, UINT screenHeight, ComPtr<ID3D11Texture2D>& depthTexture, ComPtr<ID3D11DepthStencilView>& depthTextureDSV);

	private:
		static DirectX11System* s_Instance;
	private:
		ComPtr<ID3D11Device> m_Device = nullptr;
		ComPtr<IDXGISwapChain> m_Swapchain = nullptr;
		ComPtr<ID3D11DeviceContext> m_Context = nullptr;
		ComPtr<ID3D11RenderTargetView> m_BackbufferRTV = nullptr;
		ComPtr<ID3D11Texture2D> m_DepthStencilBuffer = nullptr;
		ComPtr<ID3D11DepthStencilView> m_DepthStencilView = nullptr;

		ComPtr<ID3D11RasterizerState> m_RasterizerState = nullptr;
		ComPtr<ID3D11DepthStencilState> m_DepthStencilState;

		ComPtr<IDXGIDevice> m_DXGIDevice = nullptr;
		ComPtr<IDXGIAdapter> m_Adapter = nullptr;
		DXGI_ADAPTER_DESC* m_AdapterDescription = nullptr;

		UINT m_NumQualityLevels;
		UINT m_WholeScreenWidth;
		UINT m_WholeScreenHeight;

		D3D11_VIEWPORT m_ScreenViewport;
	};
}