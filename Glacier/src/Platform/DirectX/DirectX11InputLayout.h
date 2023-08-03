#pragma once

#include "Glacier/Renderer/VertexLayout.h"
#include "Glacier/Renderer/Shader.h"

#include <d3d11.h>
#include <wrl.h>

namespace Glacier
{
	using Microsoft::WRL::ComPtr;

	class DirectX11InputLayout : public VertexLayout
	{
	public:
		DirectX11InputLayout(VertexShader* vertexShdaer);
		virtual ~DirectX11InputLayout();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual uint32 GetVertexStride() const override { return m_Stride; }

	private:
		void CreateInputLayoutFromVertexShader(VertexShader* vertexShdaer);

		ComPtr<ID3D11InputLayout> m_InputLayout;
		uint32 m_Stride;
	};
}