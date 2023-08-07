#include "pch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Platform/DirectX/Buffer/DirectX11VertexBuffer.h"
#include "Platform/DirectX/Buffer/DirectX11IndexBuffer.h"

namespace Glacier
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32 size)
	{
		// ����ϴ� �׷��Ƚ� API�� ���� ����, �ε��� ���۸� �����ϴ� ����� �ٸ��� ������ �� API�� ���� ������ ����, �ε��� ���� Ŭ������ �ν��Ͻ��� ��������.
		switch (Renderer::GetAPI())
		{
		case GraphicsAPI::API::None:    GR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case GraphicsAPI::API::DirectX11:  return new DirectX11VertexBuffer(vertices, size);
		}

		GR_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32 size, BufferLayout& layout)
	{
		switch (Renderer::GetAPI())
		{
			case GraphicsAPI::API::None:    GR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case GraphicsAPI::API::DirectX11:  return new DirectX11VertexBuffer(vertices, size, layout);
		}

		GR_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32* indices, uint32 size)
	{
		switch (Renderer::GetAPI())
		{
			case GraphicsAPI::API::None:    GR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case GraphicsAPI::API::DirectX11:  return new DirectX11IndexBuffer(indices, size);
		}

		GR_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}