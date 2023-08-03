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
		// ���� �������� StructureByteStride�� ����ϴ� ���, layout�� ���� ���� �������� ũ�⸦���� ����� �־�� ��.
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

		uint32 m_stride; // stride�� vertex buffer �ȿ� ��� �ִ� �� ������ ũ��.
		uint32 m_offset; // offset�� vertex buffer array ���� ���. vertex buffer array���� vertex buffer���� ������ ũ��.
	};
}