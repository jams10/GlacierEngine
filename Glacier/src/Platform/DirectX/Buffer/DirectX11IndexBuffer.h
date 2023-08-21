#pragma once

#include "Glacier/Renderer/Buffer.h"

#include <d3d11.h>
#include <wrl.h>

namespace Glacier
{
	using Microsoft::WRL::ComPtr;

	class GLACIER_API DirectX11IndexBuffer : public IndexBuffer
	{
	public:
		DirectX11IndexBuffer(uint32* indices, uint32 count);
		virtual ~DirectX11IndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual uint32 GetCount() const { return m_Count; }

	private:
		ComPtr<ID3D11Buffer> m_gpuBuffer;
		uint32 m_Count;
	};
}