#pragma once

#include "Glacier/Core/Core.h"
#include "Glacier/Renderer/Buffer.h"

#include <d3d11.h>
#include <wrl.h>

namespace Glacier
{
	using Microsoft::WRL::ComPtr;

	class GLACIER_API DirectX11ConstantBuffer : public ShaderBuffer
	{
	public:
		DirectX11ConstantBuffer(void* data, uint32 size, ShaderBufferType type);
		~DirectX11ConstantBuffer();

		virtual void Bind(const uint8& slot) override;
		virtual void Unbind() const override;

		virtual void UpdateData(void* data, uint32 size) override;

		inline const ShaderBufferType& GetBufferType() const { return m_BufferType; }
		inline const ComPtr<ID3D11Buffer>& GetGPUBuffer() const { return m_GpuBuffer; }

	private:
		ComPtr<ID3D11Buffer> m_GpuBuffer;
		ShaderBufferType m_BufferType;
		uint8 m_BindingSlot;
	};
}