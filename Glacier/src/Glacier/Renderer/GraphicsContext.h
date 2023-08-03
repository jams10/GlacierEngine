#pragma once

#include "Glacier/Core.h"

namespace Glacier
{
	struct ContextInfo 
	{
		std::string Vendor;
		std::string Renderer;
		std::string API;
		std::string Version;
	};

	class GLACIER_API GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}