#pragma once

namespace Glacier
{
	struct ContextInfo 
	{
		std::string Vendor;
		std::string Renderer;
		std::string API;
		std::string Version;
	};

	class GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}