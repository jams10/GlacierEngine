#pragma once

#include "Glacier/Core.h"

#include "Glacier/Types.h"

namespace Glacier 
{
	/* 
		정점의 경우 유연하게 구성할 수 있음.
		정점 버퍼를 만들 때 각 정점 데이터의 크기를 알아야 하기 때문에 유연하게 구성할 수 있는 정점 데이터의 크기를 계산하기 위해 아래와 같은 작업들을 수행.
		또한 상수 버퍼의 경우에도 자유롭게 데이터들을 구성할 수 있기 때문에 런타임에 버퍼의 데이터 구조를 파악할 수 있어야 함.
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

	// 버퍼를 구성하는 각 element.
	struct BufferElement
	{
		std::string Name;    // element의 이름.
		ShaderDataType Type; // 해당 element의 데이터 유형.
		uint32 Size;         // 해당 element의 데이터 크기.
		uint32 Offset;       // 각 element의 정점 데이터안에서의 시작 지점. [float4, float2]로 데이터가 구성될 경우, 두 번째 element의 경우 시작 지점이 4가 됨.
		bool Normalized;     // 해당 element를 해석할 때 정규화된 값[0~1]으로 해석할 것인지 여부.

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

	// 버퍼를 구성하는 데이터의 구조를 정의.
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
		uint32 m_Stride = 0; // 데이터 간의 간격. ex) [정점1]<->[정점2]
	};


	/*
		정점 버퍼 클래스.
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
		인덱스 버퍼 클래스.
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
		쉐이더 버퍼 클래스. (DirectX의 상수 버퍼)
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