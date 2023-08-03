#pragma once

#include "RenderAPI.h"

namespace Glacier 
{
	/*
		렌더 API를 사용해서 렌더링을 진행할 때 사용하는 각종 렌더링 명령들을 호출하는 클래스.
		사용하는 렌더 API에 따라 RenderAPI 클래스를 상속 받은 자식 클래스를 호출, 구체적인 렌더 API를 호출함.
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