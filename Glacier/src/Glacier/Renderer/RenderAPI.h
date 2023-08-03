#pragma once

#include <glm/glm.hpp>
#include <memory>

#include "Buffer.h"

namespace Glacier 
{
	class RenderAPI
	{
	public:
		enum class API
		{
			None = 0, DirectX11 = 1,
		};
	public:
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void BeginRenderFrame() = 0;

		virtual void DrawIndexed(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

		inline static API GetAPI() { return s_API; }
	private:
		static API s_API;
	};

}