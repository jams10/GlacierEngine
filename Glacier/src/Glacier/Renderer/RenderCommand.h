#pragma once

#include "Glacier/Core/Core.h"
#include "GraphicsAPI.h"

namespace Glacier 
{
	/*
		렌더 API를 사용해서 렌더링을 진행할 때 사용하는 각종 렌더링 명령들을 호출하는 클래스.
		사용하는 렌더 API에 따라 RenderAPI 클래스를 상속 받은 자식 클래스를 호출, 구체적인 렌더 API를 호출함.
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