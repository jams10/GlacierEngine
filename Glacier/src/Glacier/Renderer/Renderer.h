#pragma once

#include "Glacier/Core/Core.h"
#include "RenderCommand.h"

#include "Buffer.h"
#include "VertexLayout.h"

namespace Glacier
{
	class GLACIER_API Renderer
	{
	public:
		static void BeginRenderScene();
		static void EndRenderScene();
		static void OnWindowResize(uint32_t width, uint32_t height);

		static void Submit(const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<IndexBuffer>& indexBuffer,
			const std::shared_ptr<VertexLayout>& vertexLayout);

		inline static GraphicsAPI::API GetAPI() { return GraphicsAPI::GetAPI(); }
	};
}