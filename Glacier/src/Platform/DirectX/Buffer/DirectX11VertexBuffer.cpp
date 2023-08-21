#include "pch.h"
#include "DirectX11VertexBuffer.h"

#include "Platform/DirectX/DirectX11Device.h"

namespace Glacier
{
#pragma region Vertex Buffer

	DirectX11VertexBuffer::DirectX11VertexBuffer(void* vertices, uint32 size)
	{
		m_Stride = 0;
		m_Offset = 0;
		m_Size = size;

		D3D11_BUFFER_DESC bufferDesc;
		ZeroMemory(&bufferDesc, sizeof(bufferDesc));
		bufferDesc.Usage = D3D11_USAGE_IMMUTABLE; // 정점 버퍼의 경우 한번 GPU로 보내면 바꿀 필요가 없음. 트랜스폼은 변환 행렬을 통해 변경 가능.
		bufferDesc.ByteWidth = size;
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.CPUAccessFlags = 0; // CPU 접근 필요 없음.
		bufferDesc.StructureByteStride = m_Stride;

		D3D11_SUBRESOURCE_DATA vertexBufferData; // 정점 버퍼에 들어갈 실제 데이터를 지정함.
		ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
		vertexBufferData.pSysMem = vertices;
		vertexBufferData.SysMemPitch = 0;
		vertexBufferData.SysMemSlicePitch = 0;

		THROWFAILED(DirectX11Device::GetDevice()->CreateBuffer(&bufferDesc, &vertexBufferData, m_GpuBuffer.GetAddressOf()));
	}

	DirectX11VertexBuffer::DirectX11VertexBuffer(void* vertices, uint32 size, BufferLayout& layout)
	{
		m_Layout = layout;
		m_Stride = layout.GetStride();
		m_Offset = 0;
		m_Size = size;

		D3D11_BUFFER_DESC bufferDesc;
		ZeroMemory(&bufferDesc, sizeof(bufferDesc));
		bufferDesc.Usage = D3D11_USAGE_IMMUTABLE; // 정점 버퍼의 경우 한번 GPU로 보내면 바꿀 필요가 없음. 트랜스폼은 변환 행렬을 통해 변경 가능.
		bufferDesc.ByteWidth = size;
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.CPUAccessFlags = 0; // CPU 접근 필요 없음.
		bufferDesc.StructureByteStride = m_Stride;

		D3D11_SUBRESOURCE_DATA vertexBufferData; // 정점 버퍼에 들어갈 실제 데이터를 지정함.
		ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
		vertexBufferData.pSysMem = vertices;
		vertexBufferData.SysMemPitch = 0;
		vertexBufferData.SysMemSlicePitch = 0;

		THROWFAILED(DirectX11Device::GetDevice()->CreateBuffer(&bufferDesc, &vertexBufferData, m_GpuBuffer.GetAddressOf()));
	}

	DirectX11VertexBuffer::~DirectX11VertexBuffer()
	{
		m_GpuBuffer = nullptr;
	}

	void DirectX11VertexBuffer::Bind() const
	{
		DirectX11Device::GetDeviceContext()->IASetVertexBuffers(0, 1, m_GpuBuffer.GetAddressOf(), &m_Stride, &m_Offset);
	}

	void DirectX11VertexBuffer::Bind(const uint32& stride) const
	{
		DirectX11Device::GetDeviceContext()->IASetVertexBuffers(0, 1, m_GpuBuffer.GetAddressOf(), &stride, &m_Offset);
	}

	void DirectX11VertexBuffer::Unbind() const
	{
		DirectX11Device::GetDeviceContext()->IASetVertexBuffers(0, 1, nullptr, nullptr, nullptr);
	}

	uint32 DirectX11VertexBuffer::GetCount() const
	{
		uint32 count = 0;
		for (auto it = m_Layout.begin(); it != m_Layout.end(); ++it)
		{
			count += it->GetComponentCount() * 4;
		}
		return m_Size / count;
	}

#pragma endregion
}