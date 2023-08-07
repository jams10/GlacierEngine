#pragma once

#include "Glacier/Renderer/GraphicsManager.h"

struct GLFWwindow;

namespace Glacier
{
	class GLACIER_API DirectX11Manager : public GraphicsManager
	{
	public:
		DirectX11Manager(void* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;

		void SetDeviceInfo();

	private:
		void* m_WindowHandle;
		DeviceInfo m_DeviceInfo;
	};
}