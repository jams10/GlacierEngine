#pragma once

#include "Glacier/Core/Core.h"
#include "Glacier/Renderer/Buffer.h"

#include <memory>

namespace Glacier
{
	/*
		����, �ε��� ���۸� �ϳ��� Mesh��� Ŭ������ ��� ������.
	*/
	class GLACIER_API Mesh
	{
	public:
		Mesh(std::shared_ptr<VertexBuffer>& vertexBuffer, std::shared_ptr<IndexBuffer>& indexBuffer);
		~Mesh();

		void Bind(const uint32& stride) const;

	private:
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
	};
}