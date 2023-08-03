#pragma once

#include "Glacier/Core.h"
#include "RenderCommand.h"

#include "Buffer.h"
#include "VertexLayout.h"

namespace Glacier
{
	/*
		���� �������ϴ� �۾��� ó���ϴ� Ŭ����.
		Renderer -> RenderCommand -> RenderAPI -> ��ü���� RenderAPI Ŭ���� ������ ���� API �Լ��� ȣ��, ���� ������ ��.��
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