#pragma once

#include "Glacier/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Glacier
{
	class DirectX11Context : public GraphicsContext
	{
	public:
		DirectX11Context(void* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;

		void SetContextInfo();

	private:
		void* m_WindowHandle;
		ContextInfo m_ContextInfo;
	};
}