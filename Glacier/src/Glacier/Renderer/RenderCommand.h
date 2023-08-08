#pragma once

#include "Glacier/Core.h"
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
		inline static void SetClearColor(float colors[4])
		{
			s_GraphicsAPI->SetClearColor(colors);
		}

		inline static void Clear()
		{
			s_GraphicsAPI->Clear();
		}

		inline static void BeginRenderFrame()
		{
			s_GraphicsAPI->BeginRenderFrame();
		}

		inline static void DrawIndexed(const std::shared_ptr<IndexBuffer>& indexBuffer)
		{
			s_GraphicsAPI->DrawIndexed(indexBuffer);
		}
	private:
		static GraphicsAPI* s_GraphicsAPI;
	};

}