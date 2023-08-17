#pragma once

#include "Glacier/Core/Core.h"

#include <string>

namespace Glacier 
{
	/*
		Á¤Á¡ ½¦ÀÌ´õ
	*/
	class GLACIER_API VertexShader
	{
	public:
		virtual ~VertexShader() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static VertexShader* Create(const std::wstring& shaderFilePath);
	};
	/*
		ÇÁ·¡±×¸ÕÆ®, ÇÈ¼¿ ½¦ÀÌ´õ
	*/
	class GLACIER_API FragmentShader
	{
	public:
		virtual ~FragmentShader() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static FragmentShader* Create(const std::wstring& shaderFilePath);
	};

	// ±âÇÏ ½¦ÀÌ´õ, ÄÄÇ»Æ® ½¦ÀÌ´õ µîµî.
}