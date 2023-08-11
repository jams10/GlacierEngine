#include "pch.h"
#include "Mesh.h"
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
		RenderCommand::DrawIndexed(m_IndexBuffer);
	}
}