
#include "pch.h"
#include "DirectX11Context.h"
#include "DirectX11System.h"

namespace Glacier
{
	DirectX11Context::DirectX11Context(void* windowHandle)
		:m_WindowHandle(windowHandle)
	{
		GR_CORE_ASSERT(windowHandle, "Window handle is null!")
	}
	void DirectX11Context::Init()
	{
		DirectX11System::GetInstance()->Init(static_cast<HWND>(m_WindowHandle));

		SetContextInfo();
	}

	void DirectX11Context::SwapBuffers()
	{
		DirectX11System::GetInstance()->GetDirectX11SwapChain()->Present(0, 0);
	}

	void DirectX11Context::SetContextInfo()
	{
		/* Code from CybernetHacker14' Sential repo : https://github.com/CybernetHacker14/Sentinel */
		char videoCardDescription[128];

		std::string vendor, major, minor, release, build, version;
		LARGE_INTEGER driverVersion;

		wcstombs_s(NULL, videoCardDescription, 128, DirectX11System::GetInstance()->GetDirectX11AdapterDescription()->Description, 128);

		if (DirectX11System::GetInstance()->GetDirectX11AdapterDescription()->VendorId == 0x10DE)
			vendor = "NVIDIA Corporation";
		else if (DirectX11System::GetInstance()->GetDirectX11AdapterDescription()->VendorId == 0x1002)
			vendor = "AMD";
		else if (DirectX11System::GetInstance()->GetDirectX11AdapterDescription()->VendorId == 0x8086)
			vendor = "Intel";
		else if (DirectX11System::GetInstance()->GetDirectX11AdapterDescription()->VendorId == 0x1414)
			vendor = "Microsoft";
		else
			vendor = "Unknown vendor!";

		DirectX11System::GetInstance()->GetDirectX11Adapter()->CheckInterfaceSupport(__uuidof(IDXGIDevice), &driverVersion);

		m_ContextInfo.Vendor = vendor;
		m_ContextInfo.Renderer = videoCardDescription;
		m_ContextInfo.API = "DirectX 11";

		major = std::to_string(HIWORD(driverVersion.HighPart)).c_str();
		minor = std::to_string(LOWORD(driverVersion.HighPart)).c_str();
		release = std::to_string(HIWORD(driverVersion.LowPart)).c_str();
		build = std::to_string(LOWORD(driverVersion.LowPart)).c_str();

		version = major + "." + minor + "." + release + "." + build;

		m_ContextInfo.Version = version;

		GR_CORE_INFO("VENDOR   : {0}", m_ContextInfo.Vendor);
		GR_CORE_INFO("RENDERER : {0}", m_ContextInfo.Renderer);
		GR_CORE_INFO("API      : {0}", m_ContextInfo.API);
		GR_CORE_INFO("VERSION  : {0}", m_ContextInfo.Version);
	}
}