#pragma once

#include "Glacier/Core/Core.h"
#include "GraphicsAPI.h"

namespace Glacier 
{
	/*
		���� API�� ����ؼ� �������� ������ �� ����ϴ� ���� ������ ��ɵ��� ȣ���ϴ� Ŭ����.
		����ϴ� ���� API�� ���� RenderAPI Ŭ������ ��� ���� �ڽ� Ŭ������ ȣ��, ��ü���� ���� API�� ȣ����.
	*/
	class GLACIER_API RenderCommand
	{
	public:

		inline static void ReizeWindow(uint32 width, uint32 height)
		{
			s_GraphicsAPI->ResizeWindow(width, height);
		}

		inline static void SetViewport(uint32 x, uint32 y, uint32 width, uint32 height)
		{
			s_GraphicsAPI->SetViewport(x, y, width, height);
		}

		inline static void ClearForRenderScene(float colors[4])
		{
			s_GraphicsAPI->ClearForRenderScene(colors);
		}

		inline static void ClearForRenderUI(float colors[4])
		{
			s_GraphicsAPI->ClearForRenderUI(colors);
		}

		inline static void SetSceneRenderTarget()
		{
			s_GraphicsAPI->SetSceneRenderTarget();
		}

		inline static void SetUIRenderTarget()
		{
			s_GraphicsAPI->SetUIRenderTarget();
		}

		inline static void DrawIndexed(const std::shared_ptr<IndexBuffer>& indexBuffer)
		{
			s_GraphicsAPI->DrawIndexed(indexBuffer);
		}

		inline static void PrepareSceneRenderedTexture()
		{
			s_GraphicsAPI->PrepareSceneRenderedTexture();
		}

		inline static void* GetSceneRenderedTexture()
		{
			return s_GraphicsAPI->GetSceneRenderedTexture();
		}


	private:
		static GraphicsAPI* s_GraphicsAPI;
	};

}