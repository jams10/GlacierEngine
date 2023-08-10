#pragma once

#include "Glacier/Core.h"
#include <memory>

#include "Buffer.h"

namespace Glacier 
{
	class GLACIER_API GraphicsAPI
	{
	public:
		enum class API
		{
			None = 0, DirectX11 = 1,
		};
	public:
		virtual void ResizeWindow(uint32 width, uint32 height) = 0;
		virtual void SetViewport(uint32 x, uint32 y, uint32 width, uint32 height) = 0;
		virtual void SetClearColor(float colors[4]) = 0;
		virtual void Clear() = 0;

		virtual void SetRenderTarget() = 0;

		virtual void DrawIndexed(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

		inline static API GetAPI() { return s_API; }
	private:
		static API s_API;
	};

}