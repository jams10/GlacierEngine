#include "pch.h"
#include "MeshGenerator.h"

#include "Glacier/Renderer/Buffer.h"

namespace Glacier
{
	std::shared_ptr<Mesh> MeshGenerator::MakeTriangle(Vector3 location)
	{
		std::shared_ptr<VertexBuffer> vertexBuffer;
		std::shared_ptr<IndexBuffer> indexBuffer;
		
		// 정점 버퍼 생성.
		float vertices[3 * 8] = {
			 0.0f + location.x,  0.5f + location.y, 0.0f + location.z, 0.5f, 0.0f, 0.0f, 0.0f, -1.0f,
			 0.5f + location.x, -0.5f + location.y, 0.0f + location.z, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
			-0.5f + location.x, -0.5f + location.y, 0.0f + location.z, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f,
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

	shared_ptr<Mesh> MeshGenerator::MakeSqaure(Vector3 location)
	{
		std::shared_ptr<VertexBuffer> vertexBuffer;
		std::shared_ptr<IndexBuffer> indexBuffer;

		// 정점 버퍼 생성.
		float vertices[4 * 8] = {
			-0.5f + location.x,  0.5f + location.y, 0.0f + location.z, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
			 0.5f + location.x,  0.5f + location.y, 0.0f + location.z, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
			 0.5f + location.x, -0.5f + location.y, 0.0f + location.z, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
			-0.5f + location.x, -0.5f + location.y, 0.0f + location.z, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f,
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

	shared_ptr<Mesh> MeshGenerator::MakeCube(Vector3 location)
	{
		std::shared_ptr<VertexBuffer> vertexBuffer;
		std::shared_ptr<IndexBuffer> indexBuffer;

		// 정점 버퍼 생성.
		float vertices[] = {
			-0.5f + location.x,  0.5f + location.y, -0.5f + location.z, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, // front
			 0.5f + location.x,  0.5f + location.y, -0.5f + location.z, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
			 0.5f + location.x, -0.5f + location.y, -0.5f + location.z, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
			-0.5f + location.x, -0.5f + location.y, -0.5f + location.z, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f,
			-0.5f + location.x,  0.5f + location.y, 0.5f + location.z, 1.0f, 0.0f, 0.0f, 0.0f,  1.0f, // back
			-0.5f + location.x, -0.5f + location.y, 0.5f + location.z, 1.0f, 1.0f, 0.0f, 0.0f,  1.0f,
			 0.5f + location.x, -0.5f + location.y, 0.5f + location.z, 0.0f, 1.0f, 0.0f, 0.0f,  1.0f,
			 0.5f + location.x,  0.5f + location.y, 0.5f + location.z, 0.0f, 0.0f, 0.0f, 0.0f,  1.0f,
			-0.5f + location.x,  0.5f + location.y, 0.5f + location.z, 0.0f, 0.0f,-1.0f, 0.0f,  0.0f, // left
			-0.5f + location.x,  0.5f + location.y, -0.5f + location.z, 1.0f, 0.0f,-1.0f, 0.0f,  0.0f,
			-0.5f + location.x, -0.5f + location.y, -0.5f + location.z, 1.0f, 1.0f,-1.0f, 0.0f,  0.0f,
			-0.5f + location.x, -0.5f + location.y, 0.5f + location.z, 0.0f, 1.0f,-1.0f, 0.0f,  0.0f,
			 0.5f + location.x,  0.5f + location.y, -0.5f + location.z, 0.0f, 0.0f, 1.0f, 0.0f,  0.0f, // right
			 0.5f + location.x,  0.5f + location.y, 0.5f + location.z, 1.0f, 0.0f, 1.0f, 0.0f,  0.0f,
			 0.5f + location.x, -0.5f + location.y, 0.5f + location.z, 1.0f, 1.0f, 1.0f, 0.0f,  0.0f,
			 0.5f + location.x, -0.5f + location.y, -0.5f + location.z, 0.0f, 1.0f, 1.0f, 0.0f,  0.0f,
			-0.5f + location.x,  0.5f + location.y, -0.5f + location.z, 0.0f, 1.0f, 0.0f, 1.0f,  0.0f, // top
			-0.5f + location.x,  0.5f + location.y, 0.5f + location.z, 0.0f, 0.0f, 0.0f, 1.0f,  0.0f,
			 0.5f + location.x,  0.5f + location.y, 0.5f + location.z, 1.0f, 0.0f, 0.0f, 1.0f,  0.0f,
			 0.5f + location.x,  0.5f + location.y, -0.5f + location.z, 1.0f, 1.0f, 0.0f, 1.0f,  0.0f,
			-0.5f + location.x, -0.5f + location.y, -0.5f + location.z, 0.0f, 0.0f, 0.0f,-1.0f,  0.0f, // down
			-0.5f + location.x, -0.5f + location.y, 0.5f + location.z, 0.0f, 1.0f, 0.0f,-1.0f,  0.0f,
			 0.5f + location.x, -0.5f + location.y, 0.5f + location.z, 1.0f, 1.0f, 0.0f,-1.0f,  0.0f,
			 0.5f + location.x, -0.5f + location.y, -0.5f + location.z, 1.0f, 0.0f, 0.0f,-1.0f,  0.0f,
		};

		vertexBuffer.reset(Glacier::VertexBuffer::Create(vertices, sizeof(vertices)));

		Glacier::BufferLayout layout = {
			{ Glacier::ShaderDataType::Float3, "Position" },
			{ Glacier::ShaderDataType::Float2, "Texcoord" },
			{ Glacier::ShaderDataType::Float3, "Normal"}
		};
		vertexBuffer->SetLayout(layout);

		// 인덱스 버퍼 생성.
		uint32 indices[] = {
			0,1,2,2,3,0,
			4,5,6,6,7,4,
			8,9,10,10,11,8,
			12,13,14,14,15,12,
			16,17,18,18,19,16,
			20,21,22,22,23,20,
		};
		indexBuffer.reset(Glacier::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32)));

		return std::make_shared<Mesh>(vertexBuffer, indexBuffer);
	}
}

