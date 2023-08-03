
#include "pch.h"
#include "DirectX11System.h"

namespace Glacier
{
	DirectX11System* DirectX11System::s_Instance = new DirectX11System();

	DirectX11System::~DirectX11System()
	{
		if (m_AdapterDescription)
		{
			delete m_AdapterDescription;
		}
		delete s_Instance;
		s_Instance = nullptr;
	}

	void DirectX11System::Init(HWND hWnd)
	{
		const D3D_DRIVER_TYPE driverType = D3D_DRIVER_TYPE_HARDWARE;

		UINT createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG; // ����� ��忡�� ����� �÷��� ���ֱ�.
#endif
		ComPtr<ID3D11Device> device;
		ComPtr<ID3D11DeviceContext> context;

		const D3D_FEATURE_LEVEL featureLevels[2] = {
			D3D_FEATURE_LEVEL_11_0, // �� ���� ������ ���� ������ ����
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

		// ������ device, device context COM �������̽��� ������ ĳ��.
		THROWFAILED(device.As(&m_Device));

		THROWFAILED(context.As(&m_Context));

		m_Device->QueryInterface(__uuidof(IDXGIDevice), (void**)&m_DXGIDevice);
		m_DXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&m_Adapter);
		m_AdapterDescription = new DXGI_ADAPTER_DESC();
		m_Adapter->GetDesc(m_AdapterDescription);

#pragma endregion Create Device & Context

		// 4X MSAA �����ϴ��� Ȯ��
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
		if (m_NumQualityLevels > 0)  // MSAA ��� �����ϸ� ���� ���� �÷���.(anti-aliasing)
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

		// rasterizer state ����.
		D3D11_RASTERIZER_DESC rastDesc;
		ZeroMemory(&rastDesc, sizeof(D3D11_RASTERIZER_DESC));
		rastDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		// rastDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
		rastDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		rastDesc.FrontCounterClockwise = false;

		m_Device->CreateRasterizerState(&rastDesc, &m_RasterizerState);

#pragma endregion Create Swapchain & Backbuffer

		CreateBackbufferViews();

		SetViewport(m_WholeScreenWidth, m_WholeScreenHeight);

#pragma region Depth Buffer
		CreateDepthBuffer(m_WholeScreenWidth, m_WholeScreenHeight, m_DepthStencilBuffer, m_DepthStencilView);

		// depth stencil state ����.
		D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
		ZeroMemory(&depthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
		depthStencilDesc.DepthEnable = true; // false
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
		if (FAILED(m_Device->CreateDepthStencilState(&depthStencilDesc, m_DepthStencilState.GetAddressOf()))) 
		{
			GR_CORE_ERROR("Failed! : CreateDepthStencilState()\n");
		}
#pragma endregion Depth Buffer

		GR_CORE_WARN("DirectX11 has initialized successfully!");
	}

	DirectX11System* DirectX11System::GetInstance()
	{
		return s_Instance;
	}

	void DirectX11System::ClearRenderTargetView()
	{
		m_Context->ClearRenderTargetView(m_BackbufferRTV.Get(), m_clearColor);
	}

	void DirectX11System::ClearDepthStencilView()
	{
		m_Context->ClearDepthStencilView(m_DepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}

	void DirectX11System::BeginFrame()
	{
		SetViewport(m_WholeScreenWidth, m_WholeScreenHeight); // �׷��� ������ ����Ʈ ����.

		ID3D11RenderTargetView* targets[] = { m_BackbufferRTV.Get() };
		m_Context->OMSetRenderTargets(1, targets, m_DepthStencilView.Get());
		m_Context->OMSetDepthStencilState(m_DepthStencilState.Get(), 0);
		m_Context->RSSetState(m_RasterizerState.Get());
	}

	void DirectX11System::CreateBackbufferViews()
	{
		// ���� ü�ο� ��� �ִ� Backbuffer�� ���� �̸� ���� Ÿ������ ������.
		ComPtr<ID3D11Texture2D> backBuffer;
		m_Swapchain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
		if (backBuffer)
		{
			if (m_BackbufferRTV != nullptr) m_BackbufferRTV.Reset();

			D3D11_TEXTURE2D_DESC desc;
			backBuffer->GetDesc(&desc);

			m_WholeScreenWidth = desc.Width;
			m_WholeScreenHeight = desc.Height;

			m_Device->CreateRenderTargetView(backBuffer.Get(), NULL, m_BackbufferRTV.GetAddressOf());
		}
		else
		{
			GR_CORE_ERROR("Backbuffer is null");
		}
	}

	void DirectX11System::SetViewport(UINT screenWidth, UINT screenHeight)
	{
		ZeroMemory(&m_ScreenViewport, sizeof(D3D11_VIEWPORT));
		m_ScreenViewport.TopLeftX = 0;
		m_ScreenViewport.TopLeftY = 0;
		m_ScreenViewport.Width = static_cast<FLOAT>(screenWidth);
		m_ScreenViewport.Height = static_cast<FLOAT>(screenHeight);
		m_ScreenViewport.MinDepth = 0.0f;
		m_ScreenViewport.MaxDepth = 1.0f; // Note: important for depth buffering

		m_Context->RSSetViewports(1, &m_ScreenViewport);
	}

	void DirectX11System::CreateDepthBuffer(UINT screenWidth, UINT screenHeight, ComPtr<ID3D11Texture2D>& depthTexture, ComPtr<ID3D11DepthStencilView>& depthTextureDSV)
	{
		if (screenWidth <= 0.0001f || screenHeight <= 0.0001f) return;
		if (depthTexture != nullptr) depthTexture.Reset();
		if (depthTextureDSV != nullptr) depthTextureDSV.Reset();

		D3D11_TEXTURE2D_DESC depthStencilBufferDesc;
		depthStencilBufferDesc.Width = screenWidth;
		depthStencilBufferDesc.Height = screenHeight;
		depthStencilBufferDesc.MipLevels = 1;
		depthStencilBufferDesc.ArraySize = 1;
		depthStencilBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		if (m_NumQualityLevels > 0)  // MSAA ��� ���ο� ���� �ٸ��� ����.
		{
			depthStencilBufferDesc.SampleDesc.Count = 4; // how many multisamples
			depthStencilBufferDesc.SampleDesc.Quality = m_NumQualityLevels - 1;
		}
		else
		{
			depthStencilBufferDesc.SampleDesc.Count = 1; // how many multisamples
			depthStencilBufferDesc.SampleDesc.Quality = 0;
		}
		depthStencilBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthStencilBufferDesc.CPUAccessFlags = 0;
		depthStencilBufferDesc.MiscFlags = 0;

		// ���� ���� ������ ���� �뵵�� �ؽ��� �ڿ��� ����.
		THROWFAILED(m_Device->CreateTexture2D(&depthStencilBufferDesc, 0, depthTexture.GetAddressOf()));
		// ���� �뵵�� ������� �ؽ��� �ڿ��� DepthStencil ���� �� �������� �˷��ֱ� ���� �ش� ���� �ؽ��ĸ� DepthStencilView�� ����.
		THROWFAILED(m_Device->CreateDepthStencilView(depthTexture.Get(), 0, &depthTextureDSV));
	}
}