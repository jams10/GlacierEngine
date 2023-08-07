#pragma once

#include "Glacier/Core.h"

namespace Glacier
{
	struct DeviceInfo 
	{
		std::string Vendor;
		std::string Renderer;
		std::string API;
		std::string Version;
	};

	class GLACIER_API GraphicsManager
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}