
#include "pch.h"
#include "DirectX11Context.h"
#include "DirectX11System.h"

namespace Glacier
{
	DirectX11Context::DirectX11Context(void* windowHandle)
		:m_WindowHandle(windowHandle)
	{
	}
	void DirectX11Context::Init()
	{
		DirectX11System::GetInstance()->Init(static_cast<HWND>(m_WindowHandle));
	}

	void DirectX11Context::SwapBuffers()
	{
		DirectX11System::GetInstance()->GetDirectX11SwapChain()->Present(0, 0);
	}
}