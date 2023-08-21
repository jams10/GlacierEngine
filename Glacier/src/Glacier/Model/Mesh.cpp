#include "pch.h"
#include "Mesh.h"
#include "Glacier/Renderer/Renderer.h"
#include "Glacier/Renderer/RenderCommand.h"

namespace Glacier
{
	Mesh::Mesh(std::shared_ptr<VertexBuffer>& vertexBuffer, std::shared_ptr<IndexBuffer>& indexBuffer)
		:m_VertexBuffer(vertexBuffer), m_IndexBuffer(indexBuffer)
	{
	}

	Mesh::~Mesh()
	{
	}

	void Mesh::Bind(const uint32& stride) const
	{
		m_VertexBuffer->Bind(stride);
		m_IndexBuffer->Bind();
		Renderer::stat.Vertices += m_VertexBuffer->GetCount();
		Renderer::stat.Indices += m_IndexBuffer->GetCount();
		Renderer::stat.Quads = Renderer::stat.Vertices / 4;
		RenderCommand::DrawIndexed(m_IndexBuffer);
		Renderer::stat.DrawCalls++;
	}
}