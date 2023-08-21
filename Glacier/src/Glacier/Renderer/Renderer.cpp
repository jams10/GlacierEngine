#include "pch.h"
#include "Renderer.h"

namespace Glacier
{
	Stat Renderer::stat;

	void Renderer::BeginRenderScene()
	{
		RenderCommand::SetRenderTarget();
	}

	void Renderer::EndRenderScene()
	{
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::ReizeWindow(width, height);
	}

	void Renderer::Submit(const std::shared_ptr<Model>& model)
	{
		model->Submit();
	}

	void Renderer::Submit(const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<IndexBuffer>& indexBuffer,
		const std::shared_ptr<VertexLayout>& vertexLayout)
	{
		vertexBuffer->Bind(vertexLayout->GetVertexStride());
		indexBuffer->Bind();
		RenderCommand::DrawIndexed(indexBuffer);
	}
}