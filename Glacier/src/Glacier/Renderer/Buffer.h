#pragma once

#include "Glacier/Core.h"

#include "Glacier/Types.h"

namespace Glacier 
{
	/* 
		������ ��� �����ϰ� ������ �� ����.
		���� ���۸� ���� �� �� ���� �������� ũ�⸦ �˾ƾ� �ϱ� ������ �����ϰ� ������ �� �ִ� ���� �������� ũ�⸦ ����ϱ� ���� �Ʒ��� ���� �۾����� ����.
		���� ��� ������ ��쿡�� �����Ӱ� �����͵��� ������ �� �ֱ� ������ ��Ÿ�ӿ� ������ ������ ������ �ľ��� �� �־�� ��.
	*/
	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static uint32 ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:    return 4;
			case ShaderDataType::Float2:   return 4 * 2;
			case ShaderDataType::Float3:   return 4 * 3;
			case ShaderDataType::Float4:   return 4 * 4;
			case ShaderDataType::Mat3:     return 4 * 3 * 3;
			case ShaderDataType::Mat4:     return 4 * 4 * 4;
			case ShaderDataType::Int:      return 4;
			case ShaderDataType::Int2:     return 4 * 2;
			case ShaderDataType::Int3:     return 4 * 3;
			case ShaderDataType::Int4:     return 4 * 4;
			case ShaderDataType::Bool:     return 1;
		}

		GR_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	// ���۸� �����ϴ� �� element.
	struct BufferElement
	{
		std::string Name;    // element�� �̸�.
		ShaderDataType Type; // �ش� element�� ������ ����.
		uint32 Size;         // �ش� element�� ������ ũ��.
		uint32 Offset;       // �� element�� ���� �����;ȿ����� ���� ����. [float4, float2]�� �����Ͱ� ������ ���, �� ��° element�� ��� ���� ������ 4�� ��.
		bool Normalized;     // �ش� element�� �ؼ��� �� ����ȭ�� ��[0~1]���� �ؼ��� ������ ����.

		BufferElement() {}

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{
		}

		uint32 GetComponentCount() const
		{
			switch (Type)
			{
				case ShaderDataType::Float:   return 1;
				case ShaderDataType::Float2:  return 2;
				case ShaderDataType::Float3:  return 3;
				case ShaderDataType::Float4:  return 4;
				case ShaderDataType::Mat3:    return 3 * 3;
				case ShaderDataType::Mat4:    return 4 * 4;
				case ShaderDataType::Int:     return 1;
				case ShaderDataType::Int2:    return 2;
				case ShaderDataType::Int3:    return 3;
				case ShaderDataType::Int4:    return 4;
				case ShaderDataType::Bool:    return 1;
			}

			GR_CORE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}
	};

	// ���۸� �����ϴ� �������� ������ ����.
	class GLACIER_API BufferLayout
	{
	public:
		BufferLayout() {}

		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: m_Elements(elements)
		{
			CalculateOffsetsAndStride();
		}

		inline uint32 GetStride() const { return m_Stride; }
		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
	private:
		void CalculateOffsetsAndStride()
		{
			uint32 offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}
	private:
		std::vector<BufferElement> m_Elements;
		uint32 m_Stride = 0; // ������ ���� ����. ex) [����1]<->[����2]
	};


	/*
		���� ���� Ŭ����.
	*/
	class GLACIER_API VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Bind(const uint32& stride) const = 0;
		virtual void Unbind() const = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

		static VertexBuffer* Create(float* vertices, uint32 size);
		static VertexBuffer* Create(float* vertices, uint32 size, BufferLayout& layout);
	};

	/*
		�ε��� ���� Ŭ����.
	*/
	class GLACIER_API IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32 GetCount() const = 0;

		static IndexBuffer* Create(uint32* indices, uint32 size);
	};

	enum class ShaderBufferType
	{
		VERTEX = 0, PIXEL, 
	};
	/*
		���̴� ���� Ŭ����. (DirectX�� ��� ����)
	*/
	class GLACIER_API ShaderBuffer
	{
	public:
		virtual ~ShaderBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void UpdateData(void* data, uint32 size) = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

		static ShaderBuffer* Create(void* data, uint32 size, ShaderBufferType type, uint8 bindingSlot);
	};
}