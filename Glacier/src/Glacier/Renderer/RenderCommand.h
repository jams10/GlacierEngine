#pragma once

#include "RenderAPI.h"

namespace Glacier 
{
	/*
		���� API�� ����ؼ� �������� ������ �� ����ϴ� ���� ������ ��ɵ��� ȣ���ϴ� Ŭ����.
		����ϴ� ���� API�� ���� RenderAPI Ŭ������ ��� ���� �ڽ� Ŭ������ ȣ��, ��ü���� ���� API�� ȣ����.
	*/
	class RenderCommand
	{
	public:
		inline static void SetClearColor(const glm::vec4& color)
		{
			s_RenderAPI->SetClearColor(color);
		}

		inline static void Clear()
		{
			s_RenderAPI->Clear();
		}

		inline static void BeginRenderFrame()
		{
			s_RenderAPI->BeginRenderFrame();
		}

		inline static void DrawIndexed(const std::shared_ptr<IndexBuffer>& indexBuffer)
		{
			s_RenderAPI->DrawIndexed(indexBuffer);
		}
	private:
		static RenderAPI* s_RenderAPI;
	};

}