#include "pch.h"
#include "DirectX11VertexBuffer.h"

#include "Platform/DirectX/DirectX11Device.h"

namespace Glacier
{
#pragma region Vertex Buffer

	DirectX11VertexBuffer::DirectX11VertexBuffer(void* vertices, uint32 size)
	{
		m_stride = 0;
		m_offset = 0;

		D3D11_BUFFER_DESC bufferDesc;
		ZeroMemory(&bufferDesc, sizeof(bufferDesc));
		bufferDesc.Usage = D3D11_USAGE_IMMUTABLE; // ���� ������ ��� �ѹ� GPU�� ������ �ٲ� �ʿ䰡 ����. Ʈ�������� ��ȯ ����� ���� ���� ����.
		bufferDesc.ByteWidth = size;
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.CPUAccessFlags = 0; // CPU ���� �ʿ� ����.
		bufferDesc.StructureByteStride = m_stride;

		D3D11_SUBRESOURCE_DATA vertexBufferData; // ���� ���ۿ� �� ���� �����͸� ������.
		ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
		vertexBufferData.pSysMem = vertices;
		vertexBufferData.SysMemPitch = 0;
		vertexBufferData.SysMemSlicePitch = 0;

		THROWFAILED(DirectX11Device::GetDevice()->CreateBuffer(&bufferDesc, &vertexBufferData, m_gpuBuffer.GetAddressOf()));
	}

	DirectX11VertexBuffer::DirectX11VertexBuffer(void* vertices, uint32 size, BufferLayout& layout)
	{
		m_Layout = layout;
		m_stride = layout.GetStride();
		m_offset = 0;

		D3D11_BUFFER_DESC bufferDesc;
		ZeroMemory(&bufferDesc, sizeof(bufferDesc));
		bufferDesc.Usage = D3D11_USAGE_IMMUTABLE; // ���� ������ ��� �ѹ� GPU�� ������ �ٲ� �ʿ䰡 ����. Ʈ�������� ��ȯ ����� ���� ���� ����.
		bufferDesc.ByteWidth = size;
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.CPUAccessFlags = 0; // CPU ���� �ʿ� ����.
		bufferDesc.StructureByteStride = m_stride;

		D3D11_SUBRESOURCE_DATA vertexBufferData; // ���� ���ۿ� �� ���� �����͸� ������.
		ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
		vertexBufferData.pSysMem = vertices;
		vertexBufferData.SysMemPitch = 0;
		vertexBufferData.SysMemSlicePitch = 0;

		THROWFAILED(DirectX11Device::GetDevice()->CreateBuffer(&bufferDesc, &vertexBufferData, m_gpuBuffer.GetAddressOf()));
	}

	DirectX11VertexBuffer::~DirectX11VertexBuffer()
	{
		m_gpuBuffer = nullptr;
	}

	void DirectX11VertexBuffer::Bind() const
	{
		DirectX11Device::GetDeviceContext()->IASetVertexBuffers(0, 1, m_gpuBuffer.GetAddressOf(), &m_stride, &m_offset);
	}

	void DirectX11VertexBuffer::Bind(const uint32& stride) const
	{
		DirectX11Device::GetDeviceContext()->IASetVertexBuffers(0, 1, m_gpuBuffer.GetAddressOf(), &stride, &m_offset);
	}

	void DirectX11VertexBuffer::Unbind() const
	{
		DirectX11Device::GetDeviceContext()->IASetVertexBuffers(0, 1, nullptr, nullptr, nullptr);
	}

#pragma endregion
}