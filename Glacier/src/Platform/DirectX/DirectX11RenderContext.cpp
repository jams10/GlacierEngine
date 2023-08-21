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
		CreateBackbufferViews();
		SetViewport(0, 0, m_WholeScreenWidth, m_WholeScreenHeight);
		CreateDepthBuffer(m_WholeScreenWidth, m_WholeScreenHeight, m_DepthStencilBuffer, m_DepthStencilView);

		m_SceneViewportWidth = m_WholeScreenWidth;
		m_SceneViewportHeight = m_WholeScreenHeight;

		CreateSceneRenderTexturesAndViews();
		CreateDepthBuffer(m_SceneViewportWidth, m_SceneViewportHeight, m_DepthStencilBufferForSceneRender, m_DepthStencilViewForSceneRender);

		GR_CORE_WARN("DirectX11RenderContext has initialized successfully!");
	}

	void DirectX11RenderContext::SetClearColorForSceneRender(float clearColor[4])
	{
		for (int i = 0; i < 4; ++i)
			m_ClearColorForSceneRender[i] = clearColor[i];
	}

	void DirectX11RenderContext::SetClearColorForUIRender(float clearColor[4])
	{
		for (int i = 0; i < 4; ++i)
			m_ClearColorForUIRender[i] = clearColor[i];
	}

	void DirectX11RenderContext::ClearRenderTargetViewForSceneRender()
	{
		DirectX11Device::GetDeviceContext()->ClearRenderTargetView(m_SceneRenderTexture2DMSRTV.Get(), m_ClearColorForSceneRender);
	}

	void DirectX11RenderContext::ClearDepthStencilViewForSceneRender()
	{
		DirectX11Device::GetDeviceContext()->ClearDepthStencilView(m_DepthStencilViewForSceneRender.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}

	void DirectX11RenderContext::ClearRenderTargetViewForUIRender()
	{
		DirectX11Device::GetDeviceContext()->ClearRenderTargetView(m_BackbufferRTV.Get(), m_ClearColorForUIRender);
	}

	void DirectX11RenderContext::ClearDepthStencilViewForUIRender()
	{
		DirectX11Device::GetDeviceContext()->ClearDepthStencilView(m_DepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}

	void DirectX11RenderContext::SetSceneRenderTarget()
	{
		SetViewport(0, 0, m_SceneViewportWidth, m_SceneViewportHeight);
		ID3D11RenderTargetView* targets[] = { m_SceneRenderTexture2DMSRTV.Get() };
		DirectX11Device::GetDeviceContext()->OMSetRenderTargets(1, targets, m_DepthStencilViewForSceneRender.Get());
	}

	void DirectX11RenderContext::SetUIRenderTarget()
	{
		SetViewport(0, 0, m_WholeScreenWidth, m_WholeScreenHeight);
		ID3D11RenderTargetView* targets[] = { m_BackbufferRTV.Get() };
		DirectX11Device::GetDeviceContext()->OMSetRenderTargets(1, targets, m_DepthStencilView.Get());
	}

	void DirectX11RenderContext::PrepareSceneRenderedTexture()
	{
		// ���� ������ �� Texture2DMS Ÿ���� �ؽ��ĸ� Texture2D Ÿ������ ��ȯ.
		DirectX11Device::GetDeviceContext()->ResolveSubresource(m_SceneRenderTexture2D.Get(), 0, m_SceneRenderTexture2DMS.Get(), 0, DXGI_FORMAT_R8G8B8A8_UNORM);
	}

	void* DirectX11RenderContext::GetSceneRenderedTextureSRV()
	{
		return m_SceneRenderTexture2DSRV.Get();
	}

	void DirectX11RenderContext::ResizeWindow(uint32 width, uint32 height)
	{
		if (width == 0 || height == 0) return;
		if (m_WholeScreenWidth == width && m_WholeScreenHeight == height) return;

		m_DepthStencilView = nullptr;
		m_DepthStencilBuffer = nullptr;

		m_BackbufferRTV = nullptr; // swapchain�� back buffer resize�� �����ϱ� ���ؼ��� swapchain�� back buffer�� ���� ��� ������ �����ؾ� ��.
		DirectX11Device::ResizeSwapchainBuffer(width, height);
		CreateBackbufferViews();
		//SetViewport(0, 0, m_WholeScreenWidth, m_WholeScreenHeight);
		CreateDepthBuffer(width, height, m_DepthStencilBuffer, m_DepthStencilView);
	}

	void DirectX11RenderContext::ResizeSceneViewport(uint32 width, uint32 height)
	{
		if (width == 0 || height == 0) return;
		if (m_SceneViewportWidth == width && m_SceneViewportHeight == height) return;

		m_SceneRenderTexture2DMS = nullptr;
		m_SceneRenderTexture2DMSRTV = nullptr;
		m_SceneRenderTexture2D = nullptr;
		m_SceneRenderTexture2DRTV = nullptr;
		m_SceneRenderTexture2DSRV = nullptr;

		m_DepthStencilViewForSceneRender = nullptr;
		m_DepthStencilBufferForSceneRender = nullptr;


	}

	void DirectX11RenderContext::CreateBackbufferViews()
	{
		if (DirectX11Device::GetSwapChain() == nullptr) return;

		// ���� ü�ο� ��� �ִ� Backbuffer�� ���� �̸� ���� Ÿ������ ������.
		ComPtr<ID3D11Texture2D> backBuffer;
		DirectX11Device::GetSwapChain()->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
		if (backBuffer)
		{
			if (m_BackbufferRTV != nullptr) m_BackbufferRTV = nullptr;

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

	void DirectX11RenderContext::CreateSceneRenderTexturesAndViews()
	{
		D3D11_TEXTURE2D_DESC textureDesc;
		ZeroMemory(&textureDesc, sizeof(textureDesc));
		textureDesc.Width = m_SceneViewportWidth;
		textureDesc.Height = m_SceneViewportHeight;
		textureDesc.MipLevels = textureDesc.ArraySize = 1;
		textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.Usage = D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET;
		textureDesc.MiscFlags = 0;
		textureDesc.CPUAccessFlags = 0;
		if (DirectX11Device::GetQualityLevels() > 0)  // MSAA ��� ���ο� ���� �ٸ��� ����.
		{
			textureDesc.SampleDesc.Count = 4; // how many multisamples
			textureDesc.SampleDesc.Quality = DirectX11Device::GetQualityLevels() - 1;
		}
		else
		{
			textureDesc.SampleDesc.Count = 1; // how many multisamples
			textureDesc.SampleDesc.Quality = 0;
		}

		// ���� �������� �ؽ��Ŀ� ���� Ÿ������ �����ϱ� ���� ���� Ÿ�� �並 ����.
		THROWFAILED(DirectX11Device::GetDevice()->CreateTexture2D(&textureDesc, nullptr, &m_SceneRenderTexture2DMS));
		THROWFAILED(DirectX11Device::GetDevice()->CreateRenderTargetView(m_SceneRenderTexture2DMS.Get(), nullptr, &m_SceneRenderTexture2DMSRTV));

		textureDesc.SampleDesc.Count = 1;
		textureDesc.SampleDesc.Quality = 0;
		textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
		textureDesc.MiscFlags = 0;

		// ��ó���� ���� ���̴� �Է����� ����� Texture2D Ÿ�� �ؽ��ĸ� �������.
		THROWFAILED(DirectX11Device::GetDevice()->CreateTexture2D(&textureDesc, nullptr, &m_SceneRenderTexture2D));
		THROWFAILED(DirectX11Device::GetDevice()->CreateRenderTargetView(m_SceneRenderTexture2D.Get(), nullptr, &m_SceneRenderTexture2DRTV));
		THROWFAILED(DirectX11Device::GetDevice()->CreateShaderResourceView(m_SceneRenderTexture2D.Get(), nullptr, &m_SceneRenderTexture2DSRV));
	}

	void DirectX11RenderContext::SetViewport(UINT topLeftX, UINT topLeftY, UINT width, UINT height)
	{
		// ������ ���� �� ��ٷ� window resize �޽����� �߻��ϱ� ������ device context ���� ���� �̺�Ʈ�� ���� SetViewport �Լ��� ȣ��� �� ����.
		// ����, DeviceContext�� ������ �Ŀ� context�� ������ viewport�� ������ �� �ֵ��� ��.
		if (DirectX11Device::GetDeviceContext() == nullptr) return;

		ZeroMemory(&m_ScreenViewport, sizeof(D3D11_VIEWPORT));
		m_ScreenViewport.TopLeftX = static_cast<FLOAT>(topLeftX);
		m_ScreenViewport.TopLeftY = static_cast<FLOAT>(topLeftY);
		m_ScreenViewport.Width = static_cast<FLOAT>(width);
		m_ScreenViewport.Height = static_cast<FLOAT>(height);
		m_ScreenViewport.MinDepth = 0.0f;
		m_ScreenViewport.MaxDepth = 1.0f; // Note: important for depth buffering

		DirectX11Device::GetDeviceContext()->RSSetViewports(1, &m_ScreenViewport);
	}

	void DirectX11RenderContext::CreateDepthBuffer(UINT screenWidth, UINT screenHeight, ComPtr<ID3D11Texture2D>& depthTexture, ComPtr<ID3D11DepthStencilView>& depthTextureDSV)
	{
		if (DirectX11Device::GetDevice() == nullptr) return;
		if (screenWidth <= 0.0001f || screenHeight <= 0.0001f) return;

		if (depthTexture != nullptr) depthTexture.Reset();
		if (depthTextureDSV != nullptr) depthTextureDSV.Reset();

		D3D11_TEXTURE2D_DESC depthStencilBufferDesc;
		depthStencilBufferDesc.Width = screenWidth;
		depthStencilBufferDesc.Height = screenHeight;
		depthStencilBufferDesc.MipLevels = 1;
		depthStencilBufferDesc.ArraySize = 1;
		depthStencilBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		if (DirectX11Device::GetQualityLevels() > 0)  // MSAA ��� ���ο� ���� �ٸ��� ����.
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

		// ���� ���� ������ ���� �뵵�� �ؽ��� �ڿ��� ����.
		THROWFAILED(DirectX11Device::GetDevice()->CreateTexture2D(&depthStencilBufferDesc, 0, depthTexture.GetAddressOf()));
		// ���� �뵵�� ������� �ؽ��� �ڿ��� DepthStencil ���� �� �������� �˷��ֱ� ���� �ش� ���� �ؽ��ĸ� DepthStencilView�� ����.
		THROWFAILED(DirectX11Device::GetDevice()->CreateDepthStencilView(depthTexture.Get(), 0, &depthTextureDSV));
	}


}