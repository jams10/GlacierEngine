#include "pch.h"
#include "MeshGenerator.h"

#include "Glacier/Renderer/Buffer.h"

namespace Glacier
{
	std::shared_ptr<Mesh> MeshGenerator::MakeTriangle()
	{
		std::shared_ptr<VertexBuffer> vertexBuffer;
		std::shared_ptr<IndexBuffer> indexBuffer;
		
		// 정점 버퍼 생성.
		float vertices[3 * 8] = {
			 0.0f,  0.5f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f, -1.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
			-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f,
		};

		vertexBuffer.reset(Glacier::VertexBuffer::Create(vertices, sizeof(vertices)));

		Glacier::BufferLayout layout = {
			{ Glacier::ShaderDataType::Float3, "Position" },
			{ Glacier::ShaderDataType::Float2, "Texcoord" },
			{ Glacier::ShaderDataType::Float3, "Normal"}
		};
		vertexBuffer->SetLayout(layout);

		// 인덱스 버퍼 생성.
		uint32 indices[3] = { 0,1,2 };
		indexBuffer.reset(Glacier::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32)));

		return std::make_shared<Mesh>(vertexBuffer, indexBuffer);
	}

	shared_ptr<Mesh> MeshGenerator::MakeSqaure()
	{
		std::shared_ptr<VertexBuffer> vertexBuffer;
		std::shared_ptr<IndexBuffer> indexBuffer;

		// 정점 버퍼 생성.
		float vertices[4 * 8] = {
			-0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
			-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f,
		};

		vertexBuffer.reset(Glacier::VertexBuffer::Create(vertices, sizeof(vertices)));

		Glacier::BufferLayout layout = {
			{ Glacier::ShaderDataType::Float3, "Position" },
			{ Glacier::ShaderDataType::Float2, "Texcoord" },
			{ Glacier::ShaderDataType::Float3, "Normal"}
		};
		vertexBuffer->SetLayout(layout);

		// 인덱스 버퍼 생성.
		uint32 indices[6] = { 0,1,2,2,3,0 };
		indexBuffer.reset(Glacier::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32)));

		return std::make_shared<Mesh>(vertexBuffer, indexBuffer);
	}
}

