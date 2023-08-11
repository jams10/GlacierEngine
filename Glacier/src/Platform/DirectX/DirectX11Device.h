#pragma once

#include "Glacier/Core/Core.h"
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

	class GLACIER_API DirectX11Device {
	public:
		~DirectX11Device();

		void Init(HWND hWnd);
		static DirectX11Device* GetInstance();

		static const ComPtr<ID3D11Device> GetDevice() { return s_Instance->m_Device; }
		static const ComPtr<IDXGISwapChain> GetSwapChain() { return s_Instance->m_Swapchain; }
		static const ComPtr<ID3D11DeviceContext> GetDeviceContext() { return s_Instance->m_Context; }
		static UINT GetQualityLevels() { return s_Instance->m_NumQualityLevels; }

		static const ComPtr<IDXGIDevice> GetDXGIDevice() { return s_Instance->m_DXGIDevice; }
		static const ComPtr<IDXGIAdapter> GetAdapter() { return s_Instance->m_Adapter; }
		static const DXGI_ADAPTER_DESC* GetAdapterDescription() { return s_Instance->m_AdapterDescription; }
		static void ResizeSwapchainBuffer(uint32 width, uint32 height);

	private:
		DirectX11Device() = default;

	private:
		static DirectX11Device* s_Instance;

	private:
		ComPtr<ID3D11Device> m_Device = nullptr;
		ComPtr<IDXGISwapChain> m_Swapchain = nullptr;
		ComPtr<ID3D11DeviceContext> m_Context = nullptr;

		ComPtr<IDXGIDevice> m_DXGIDevice = nullptr;
		ComPtr<IDXGIAdapter> m_Adapter = nullptr;
		DXGI_ADAPTER_DESC* m_AdapterDescription = nullptr;

		UINT m_NumQualityLevels;
	};
}