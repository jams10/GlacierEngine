#pragma once

#include "Glacier/Renderer/Buffer.h"

#include <d3d11.h>
#include <wrl.h>

namespace Glacier 
{
	using Microsoft::WRL::ComPtr;

	class GLACIER_API DirectX11VertexBuffer : public VertexBuffer
	{
	public:
		DirectX11VertexBuffer(float* vertices, uint32 size);
		DirectX11VertexBuffer(float* vertices, uint32 size, BufferLayout& layout);
		virtual ~DirectX11VertexBuffer();

		virtual void Bind() const override;
		virtual void Bind(const uint32& stride) const override;
		virtual void Unbind() const override;

		virtual const BufferLayout& GetLayout() const override { return m_Layout; }
		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
	private:
		ComPtr<ID3D11Buffer> m_gpuBuffer;
		BufferLayout m_Layout;

		uint32 m_stride; // stride는 vertex buffer 안에 들어 있는 각 정점의 크기.
		uint32 m_offset; // offset은 vertex buffer array 사용시 사용. vertex buffer array에서 vertex buffer간의 오프셋 크기.
	};
}