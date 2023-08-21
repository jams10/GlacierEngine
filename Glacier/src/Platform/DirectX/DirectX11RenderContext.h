#pragma once

#include "Glacier/Core/Core.h"

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

		void SetClearColorForSceneRender(float clearColor[4]);
		void SetClearColorForUIRender(float clearColor[4]);
		void ClearRenderTargetViewForSceneRender();
		void ClearDepthStencilViewForSceneRender();
		void ClearRenderTargetViewForUIRender();
		void ClearDepthStencilViewForUIRender();
		void SetViewport(UINT startX , UINT startY, UINT screenWidth, UINT screenHeight);
		void ResizeWindow(uint32 width, uint32 height);
		void ResizeSceneViewport(uint32 width, uint32 height);
		void SetSceneRenderTarget();
		void SetUIRenderTarget();

		void PrepareSceneRenderedTexture();
		void* GetSceneRenderedTextureSRV();

	private:
		DirectX11RenderContext() = default;

		void CreateBackbufferViews();
		void CreateSceneRenderTexturesAndViews();
		void CreateDepthBuffer(UINT screenWidth, UINT screenHeight, ComPtr<ID3D11Texture2D>& depthTexture, ComPtr<ID3D11DepthStencilView>& depthTextureDSV);

	private:
		static DirectX11RenderContext* s_Instance;

	private:
		// UI �������� ���� �ʿ��� ���ҽ�.
		ComPtr<ID3D11RenderTargetView> m_BackbufferRTV = nullptr;
		ComPtr<ID3D11Texture2D> m_DepthStencilBuffer = nullptr;
		ComPtr<ID3D11DepthStencilView> m_DepthStencilView = nullptr;
		// UI �������� ���� �ʿ��� ���ҽ�.

		// �� �������� ���� �ʿ��� ���ҽ�.
		ComPtr<ID3D11Texture2D> m_SceneRenderTexture2DMS = nullptr;
		ComPtr<ID3D11RenderTargetView> m_SceneRenderTexture2DMSRTV = nullptr;
		// �� �������� ����� �ؽ��ĸ� MSAA�� ����ϵ��� ����� Texture2DMS Ÿ���� �Ǵµ�, �̴� ���̴� ����ϱ� ��ٷӱ� ������ ��ó���� ���� Texture2D�� ������ ���.
		ComPtr<ID3D11Texture2D> m_SceneRenderTexture2D = nullptr;
		ComPtr<ID3D11RenderTargetView> m_SceneRenderTexture2DRTV = nullptr;
		ComPtr<ID3D11ShaderResourceView> m_SceneRenderTexture2DSRV = nullptr;
		ComPtr<ID3D11Texture2D> m_DepthStencilBufferForSceneRender = nullptr;
		ComPtr<ID3D11DepthStencilView> m_DepthStencilViewForSceneRender = nullptr;
		// �� �������� ���� �ʿ��� ���ҽ�.

		float m_ClearColorForSceneRender[4];
		float m_ClearColorForUIRender[4];
		UINT m_WholeScreenWidth;
		UINT m_WholeScreenHeight;
		UINT m_SceneViewportWidth;
		UINT m_SceneViewportHeight;
		D3D11_VIEWPORT m_ScreenViewport;
	};
}