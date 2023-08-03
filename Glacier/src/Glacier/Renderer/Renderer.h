#pragma once

#include "Glacier/Core.h"

namespace Glacier
{
	enum class RendererAPI
	{
		None = 0,
		DirectX11 = 1,
	};

	class GLACIER_API Renderer
	{
	public:
		inline static RendererAPI GetAPI() { return s_RendererAPI; }
	private:
		static RendererAPI s_RendererAPI;
	};
}