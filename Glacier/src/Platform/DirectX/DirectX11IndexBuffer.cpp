#include "pch.h"
#include "DirectX11IndexBuffer.h"

#include "DirectX11System.h"

namespace Glacier
{
	DirectX11IndexBuffer::DirectX11IndexBuffer(uint32* indices, uint32 count)
		: m_Count(count)
	{
		D3D11_BUFFER_DESC bufferDesc = {};
		bufferDesc.Usage = D3D11_USAGE_IMMUTABLE; // 인덱스 버퍼 또한 정점 버퍼와 같이 한 번 GPU로 보내면 바꿀 필요가 없음.
		bufferDesc.ByteWidth = UINT(sizeof(uint32) * count);
		bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bufferDesc.CPUAccessFlags = 0;
		bufferDesc.StructureByteStride = sizeof(uint32);

		D3D11_SUBRESOURCE_DATA indexBufferData;
		ZeroMemory(&indexBufferData, sizeof(indexBufferData));
		indexBufferData.pSysMem = indices;
		indexBufferData.SysMemPitch = 0;
		indexBufferData.SysMemSlicePitch = 0;

		THROWFAILED(DirectX11System::GetInstance()->GetDirectX11Device()->CreateBuffer(&bufferDesc, &indexBufferData, m_gpuBuffer.GetAddressOf()));
	}

	DirectX11IndexBuffer::~DirectX11IndexBuffer()
	{
		m_gpuBuffer = nullptr;
	}

	void DirectX11IndexBuffer::Bind() const
	{
		DirectX11System::GetInstance()->GetDirectX11DeviceContext()->IASetIndexBuffer(m_gpuBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	}

	void DirectX11IndexBuffer::Unbind() const
	{
		DirectX11System::GetInstance()->GetDirectX11DeviceContext()->IASetIndexBuffer(nullptr, DXGI_FORMAT_R32_UINT, 0);
	}
}

