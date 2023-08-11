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

		inline static void SetClearColor(float colors[4])
		{
			s_GraphicsAPI->SetClearColor(colors);
		}

		inline static void Clear()
		{
			s_GraphicsAPI->Clear();
		}

		inline static void SetRenderTarget()
		{
			s_GraphicsAPI->SetRenderTarget();
		}

		inline static void DrawIndexed(const std::shared_ptr<IndexBuffer>& indexBuffer)
		{
			s_GraphicsAPI->DrawIndexed(indexBuffer);
		}
	private:
		static GraphicsAPI* s_GraphicsAPI;
	};

}