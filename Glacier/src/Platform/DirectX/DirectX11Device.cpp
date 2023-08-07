
#include "pch.h"
#include "DirectX11Device.h"

namespace Glacier
{
	DirectX11Device* DirectX11Device::s_Instance = new DirectX11Device();

	DirectX11Device::~DirectX11Device()
	{
		if (m_AdapterDescription)
		{
			delete m_AdapterDescription;
		}
		delete s_Instance;
		s_Instance = nullptr;
	}

	void DirectX11Device::Init(HWND hWnd)
	{
		const D3D_DRIVER_TYPE driverType = D3D_DRIVER_TYPE_HARDWARE;

		UINT createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG; // 디버그 모드에서 디버깅 플래그 켜주기.
#endif
		ComPtr<ID3D11Device> device;
		ComPtr<ID3D11DeviceContext> context;

		const D3D_FEATURE_LEVEL featureLevels[2] = {
			D3D_FEATURE_LEVEL_11_0, // 더 높은 버전이 먼저 오도록 설정
			D3D_FEATURE_LEVEL_9_3 };
		D3D_FEATURE_LEVEL featureLevel;

#pragma region Create Device & Context
		THROWFAILED(D3D11CreateDevice(
			nullptr,					// Specify nullptr to use the default adapter.
			driverType,					// Create a device using the hardware graphics driver.
			0,							// Should be 0 unless the driver is D3D_DRIVER_TYPE_SOFTWARE.
			createDeviceFlags,			// Set debug and Direct2D compatibility flags.
			featureLevels,				// List of feature levels this app can support.
			ARRAYSIZE(featureLevels),	// Size of the list above.
			D3D11_SDK_VERSION,			// Always set this to D3D11_SDK_VERSION for Microsoft Store apps.
			&device,					// Returns the Direct3D device created.
			&featureLevel,				// Returns feature level of device created.
			&context					// Returns the device immediate context.
		));

		if (featureLevel != D3D_FEATURE_LEVEL_11_0)
		{
			GR_CORE_ERROR("D3D Feature Level 11 unsupported.\n");
		}

		// 생성한 device, device context COM 인터페이스를 가져와 캐싱.
		THROWFAILED(device.As(&m_Device));

		THROWFAILED(context.As(&m_Context));

		m_Device->QueryInterface(__uuidof(IDXGIDevice), (void**)&m_DXGIDevice);
		m_DXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&m_Adapter);
		m_AdapterDescription = new DXGI_ADAPTER_DESC();
		m_Adapter->GetDesc(m_AdapterDescription);

#pragma endregion Create Device & Context

		// 4X MSAA 지원하는지 확인
		m_Device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m_NumQualityLevels);
		if (m_NumQualityLevels <= 0)
		{
			GR_CORE_ERROR("MSAA not supported.\n");
		}

		DXGI_SWAP_CHAIN_DESC description;
		ZeroMemory(&description, sizeof(DXGI_SWAP_CHAIN_DESC));
		description.BufferDesc.Width = 0;
		description.BufferDesc.Height = 0;
		description.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		description.BufferDesc.RefreshRate.Numerator = 0;
		description.BufferDesc.RefreshRate.Denominator = 0;
		description.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		description.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		description.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		description.BufferCount = 1;
		description.OutputWindow = hWnd;
		description.Windowed = true;
		description.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		description.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		if (m_NumQualityLevels > 0)  // MSAA 사용 가능하면 샘플 수를 늘려줌.(anti-aliasing)
		{
			description.SampleDesc.Count = 4; // how many multisamples
			description.SampleDesc.Quality = m_NumQualityLevels - 1;
		}
		else
		{
			description.SampleDesc.Count = 1; // how many multisamples
			description.SampleDesc.Quality = 0;
		}

		// Create the device and the swapchain
		auto result = D3D11CreateDeviceAndSwapChain(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			D3D11_CREATE_DEVICE_DEBUG,
			nullptr,
			0,
			D3D11_SDK_VERSION,
			&description,
			&m_Swapchain,
			&m_Device,
			nullptr,
			&m_Context
		);

		//// rasterizer state 생성.
		//D3D11_RASTERIZER_DESC rastDesc;
		//ZeroMemory(&rastDesc, sizeof(D3D11_RASTERIZER_DESC));
		//rastDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		//// rastDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
		//rastDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		//rastDesc.FrontCounterClockwise = false;

		//m_Device->CreateRasterizerState(&rastDesc, &m_RasterizerState);

#pragma endregion Create Swapchain & Backbuffer

		//CreateBackbufferViews();

		//SetViewport(m_WholeScreenWidth, m_WholeScreenHeight);

#pragma region Depth Buffer
		//CreateDepthBuffer(m_WholeScreenWidth, m_WholeScreenHeight, m_DepthStencilBuffer, m_DepthStencilView);

		// depth stencil state 생성.
		//D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
		//ZeroMemory(&depthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
		//depthStencilDesc.DepthEnable = true; // false
		//depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		//depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
		//if (FAILED(m_Device->CreateDepthStencilState(&depthStencilDesc, m_DepthStencilState.GetAddressOf()))) 
		//{
		//	GR_CORE_ERROR("Failed! : CreateDepthStencilState()\n");
		//}
#pragma endregion Depth Buffer

		GR_CORE_WARN("DirectX11Device has initialized successfully!");
	}

	DirectX11Device* DirectX11Device::GetInstance()
	{
		return s_Instance;
	}
}