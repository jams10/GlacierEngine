#include "pch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Platform/DirectX/Buffer/DirectX11VertexBuffer.h"
#include "Platform/DirectX/Buffer/DirectX11IndexBuffer.h"

namespace Glacier
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32 size)
	{
		// 사용하는 그래픽스 API에 따라 정점, 인덱스 버퍼를 생성하는 방법이 다르기 때문에 각 API에 따라 구현한 정점, 인덱스 버퍼 클래스의 인스턴스를 생성해줌.
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