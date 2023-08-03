#pragma once

#include "Glacier/Core.h"
#include "RenderCommand.h"

#include "Buffer.h"
#include "VertexLayout.h"

namespace Glacier
{
	/*
		씬을 렌더링하는 작업을 처리하는 클래스.
		Renderer -> RenderCommand -> RenderAPI -> 구체적인 RenderAPI 클래스 순으로 렌더 API 함수를 호출, 씬을 렌더링 함.ㅋ
	*/
	class GLACIER_API Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<IndexBuffer>& indexBuffer,
			const std::shared_ptr<VertexLayout>& vertexLayout);

		inline static RenderAPI::API GetAPI() { return RenderAPI::GetAPI(); }
	};
}