#include "pch.h"
#include "DirectX11RenderContext.h"

#include "DirectX11Device.h"

namespace Glacier
{
	DirectX11RenderContext* DirectX11RenderContext::s_Instance = new DirectX11RenderContext();

	DirectX11RenderContext::~DirectX11RenderContext()
	{
		delete s_Instance;
		s_Instance = nullptr;
	}

	void DirectX11RenderContext::Init()
	{
		SetViewport(m_WholeScreenWidth, m_WholeScreenHeight);
		CreateBackbufferViews();
		CreateDepthBuffer(m_WholeScreenWidth, m_WholeScreenHeight, m_DepthStencilBuffer, m_DepthStencilView);

		GR_CORE_WARN("DirectX11RenderContext has initialized successfully!");
	}

	void DirectX11RenderContext::SetClearColor(float clearColor[4])
	{
		for (int i = 0; i < 4; ++i)
			m_ClearColor[i] = clearColor[i];
	}

	void DirectX11RenderContext::ClearRenderTargetView()
	{
		DirectX11Device::GetDeviceContext()->ClearRenderTargetView(m_BackbufferRTV.Get(), m_ClearColor);
	}

	void DirectX11RenderContext::ClearDepthStencilView()
	{
		DirectX11Device::GetDeviceContext()->ClearDepthStencilView(m_DepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}

	void DirectX11RenderContext::SetRenderTarget()
	{
		SetViewport(m_WholeScreenWidth, m_WholeScreenHeight);

		ID3D11RenderTargetView* targets[] = { m_BackbufferRTV.Get() };
		DirectX11Device::GetDeviceContext()->OMSetRenderTargets(1, targets, m_DepthStencilView.Get());
	}

	void DirectX11RenderContext::CreateBackbufferViews()
	{
		// 스왑 체인에 들어 있는 Backbuffer를 얻어와 이를 렌더 타겟으로 설정함.
		ComPtr<ID3D11Texture2D> backBuffer;
		DirectX11Device::GetSwapChain()->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
		if (backBuffer)
		{
			if (m_BackbufferRTV != nullptr) m_BackbufferRTV.Reset();

			D3D11_TEXTURE2D_DESC desc;
			backBuffer->GetDesc(&desc);

			m_WholeScreenWidth = desc.Width;
			m_WholeScreenHeight = desc.Height;

			DirectX11Device::GetDevice()->CreateRenderTargetView(backBuffer.Get(), NULL, m_BackbufferRTV.GetAddressOf());
		}
		else
		{
			GR_CORE_ERROR("Backbuffer is null");
		}
	}

	void DirectX11RenderContext::SetViewport(UINT screenWidth, UINT screenHeight)
	{
		ZeroMemory(&m_ScreenViewport, sizeof(D3D11_VIEWPORT));
		m_ScreenViewport.TopLeftX = 0;
		m_ScreenViewport.TopLeftY = 0;
		m_ScreenViewport.Width = static_cast<FLOAT>(screenWidth);
		m_ScreenViewport.Height = static_cast<FLOAT>(screenHeight);
		m_ScreenViewport.MinDepth = 0.0f;
		m_ScreenViewport.MaxDepth = 1.0f; // Note: important for depth buffering

		DirectX11Device::GetDeviceContext()->RSSetViewports(1, &m_ScreenViewport);
	}

	void DirectX11RenderContext::CreateDepthBuffer(UINT screenWidth, UINT screenHeight, ComPtr<ID3D11Texture2D>& depthTexture, ComPtr<ID3D11DepthStencilView>& depthTextureDSV)
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
		if (DirectX11Device::GetQualityLevels() > 0)  // MSAA 사용 여부에 따라 다르게 설정.
		{
			depthStencilBufferDesc.SampleDesc.Count = 4; // how many multisamples
			depthStencilBufferDesc.SampleDesc.Quality = DirectX11Device::GetQualityLevels() - 1;
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

		// 깊이 값을 저장할 버퍼 용도의 텍스쳐 자원을 생성.
		THROWFAILED(DirectX11Device::GetDevice()->CreateTexture2D(&depthStencilBufferDesc, 0, depthTexture.GetAddressOf()));
		// 버퍼 용도로 만들어준 텍스쳐 자원을 DepthStencil 값을 쓸 목적임을 알려주기 위해 해당 버퍼 텍스쳐를 DepthStencilView에 연결.
		THROWFAILED(DirectX11Device::GetDevice()->CreateDepthStencilView(depthTexture.Get(), 0, &depthTextureDSV));
	}


}