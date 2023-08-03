#include "pch.h"
#include "Renderer.h"

namespace Glacier
{
	void Renderer::BeginScene()
	{
		RenderCommand::BeginRenderFrame();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<IndexBuffer>& indexBuffer,
		const std::shared_ptr<VertexLayout>& vertexLayout)
	{
		vertexBuffer->Bind(vertexLayout->GetVertexStride());
		indexBuffer->Bind();
		RenderCommand::DrawIndexed(indexBuffer);
	}
}