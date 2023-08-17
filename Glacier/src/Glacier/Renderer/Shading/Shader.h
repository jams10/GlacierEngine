#pragma once

#include "Glacier/Core/Core.h"

#include <string>

namespace Glacier 
{
	/*
		���� ���̴�
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
		�����׸�Ʈ, �ȼ� ���̴�
	*/
	class GLACIER_API FragmentShader
	{
	public:
		virtual ~FragmentShader() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static FragmentShader* Create(const std::wstring& shaderFilePath);
	};

	// ���� ���̴�, ��ǻƮ ���̴� ���.
}