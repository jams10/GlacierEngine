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