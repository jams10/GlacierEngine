#include "pch.h"
#include "DirectX11ConstantBuffer.h"
#include "Platform/DirectX/DirectX11Device.h"

namespace Glacier
{
	DirectX11ConstantBuffer::DirectX11ConstantBuffer(void* data, uint32 size, ShaderBufferType type)
	{
		m_BufferType = type;

		D3D11_BUFFER_DESC desc;
		desc.ByteWidth = size;
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; // 상수 버퍼의 경우 CPU 쪽에서 map을 통해 값을 업데이트 해야함.
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA InitData;
		InitData.pSysMem = data;
		InitData.SysMemPitch = 0;
		InitData.SysMemSlicePitch = 0;

		THROWFAILED(DirectX11Device::GetDevice()->CreateBuffer(&desc, &InitData, m_GpuBuffer.GetAddressOf()));
	}

	DirectX11ConstantBuffer::~DirectX11ConstantBuffer()
	{
		m_GpuBuffer = nullptr;
	}

	void DirectX11ConstantBuffer::Bind(uint8 slot)
	{
		m_BindingSlot = slot;

		switch (m_BufferType)
		{
		case ShaderBufferType::VERTEX:
			DirectX11Device::GetDeviceContext()->VSSetConstantBuffers(slot, 1, m_GpuBuffer.GetAddressOf());
			break;
		case ShaderBufferType::PIXEL:
			DirectX11Device::GetDeviceContext()->PSSetConstantBuffers(slot, 1, m_GpuBuffer.GetAddressOf());
			break;
		}
	}

	void DirectX11ConstantBuffer::Unbind() const
	{
		switch (m_BufferType)
		{
		case ShaderBufferType::VERTEX:
			DirectX11Device::GetDeviceContext()->VSSetConstantBuffers(m_BindingSlot, 1, nullptr);
			break;
		case ShaderBufferType::PIXEL:
			DirectX11Device::GetDeviceContext()->PSSetConstantBuffers(m_BindingSlot, 1, nullptr);
			break;
		}
	}

	void DirectX11ConstantBuffer::UpdateData(void* data, uint32 size)
	{
		D3D11_MAPPED_SUBRESOURCE ms;
		DirectX11Device::GetDeviceContext()->Map(m_GpuBuffer.Get(), NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
		memcpy(ms.pData, data, size);
		DirectX11Device::GetDeviceContext()->Unmap(m_GpuBuffer.Get(), NULL);
	}

	void DirectX11ConstantBuffer::SetLayout(const BufferLayout& layout)
	{
	}
}