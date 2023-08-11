#pragma once

#include "Glacier/Core/Core.h"

#include "Shader.h"

namespace Glacier
{
	/*
		DX�� InputLayout, OpenGL�� VAO ó��.
	*/
	class GLACIER_API VertexLayout
	{
	public:
		virtual ~VertexLayout() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32 GetVertexStride() const = 0;

		static VertexLayout* Create();
		static VertexLayout* Create(VertexShader* vertexShader);
	};
}