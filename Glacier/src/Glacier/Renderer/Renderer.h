#pragma once

#include "Glacier/Core/Core.h"
#include "RenderCommand.h"

#include "Buffer.h"
#include "VertexLayout.h"
#include "Glacier/Model/Model.h"

namespace Glacier
{
	struct GLACIER_API Stat
	{
		uint16 DrawCalls = 0;
		uint32 Quads = 0;
		uint32 Vertices = 0;
		uint32 Indices = 0;
	};

	class GLACIER_API Renderer
	{
	public:
		static void BeginRenderScene();
		static void EndRenderScene();
		static void BeginRenderUI();
		static void OnWindowResize(uint32_t width, uint32_t height);

		static void Submit(const std::shared_ptr<Model>& model);
		static void Submit(const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<IndexBuffer>& indexBuffer,
			const std::shared_ptr<VertexLayout>& vertexLayout);

		static Stat stat;
		static void ResetStat() { stat = Stat{ 0,0,0,0 }; }
		inline static Stat GetStats() { return stat; }

		inline static GraphicsAPI::API GetAPI() { return GraphicsAPI::GetAPI(); }
	};
}