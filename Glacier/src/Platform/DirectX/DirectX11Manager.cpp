
#include "pch.h"
#include "DirectX11Manager.h"
#include "DirectX11Device.h"
#include "DirectX11RenderContext.h"

namespace Glacier
{
	DirectX11Manager::DirectX11Manager(void* windowHandle)
		:m_WindowHandle(windowHandle)
	{
		GR_CORE_ASSERT(windowHandle, "Window handle is null!")
	}
	void DirectX11Manager::Init()
	{
		DirectX11Device::GetInstance()->Init(static_cast<HWND>(m_WindowHandle));
		SetDeviceInfo();

		DirectX11RenderContext::GetInstance()->Init();
	}

	void DirectX11Manager::SwapBuffers()
	{
		DirectX11Device::GetSwapChain()->Present(0, 0);
	}

	void DirectX11Manager::SetDeviceInfo()
	{
		/* Code from CybernetHacker14' Sential repo : https://github.com/CybernetHacker14/Sentinel */
		char videoCardDescription[128];

		std::string vendor, major, minor, release, build, version;
		LARGE_INTEGER driverVersion;

		wcstombs_s(NULL, videoCardDescription, 128, DirectX11Device::GetAdapterDescription()->Description, 128);

		if (DirectX11Device::GetAdapterDescription()->VendorId == 0x10DE)
			vendor = "NVIDIA Corporation";
		else if (DirectX11Device::GetAdapterDescription()->VendorId == 0x1002)
			vendor = "AMD";
		else if (DirectX11Device::GetAdapterDescription()->VendorId == 0x8086)
			vendor = "Intel";
		else if (DirectX11Device::GetAdapterDescription()->VendorId == 0x1414)
			vendor = "Microsoft";
		else
			vendor = "Unknown vendor!";

		DirectX11Device::GetAdapter()->CheckInterfaceSupport(__uuidof(IDXGIDevice), &driverVersion);

		m_DeviceInfo.Vendor = vendor;
		m_DeviceInfo.Renderer = videoCardDescription;
		m_DeviceInfo.API = "DirectX 11";

		major = std::to_string(HIWORD(driverVersion.HighPart)).c_str();
		minor = std::to_string(LOWORD(driverVersion.HighPart)).c_str();
		release = std::to_string(HIWORD(driverVersion.LowPart)).c_str();
		build = std::to_string(LOWORD(driverVersion.LowPart)).c_str();

		version = major + "." + minor + "." + release + "." + build;

		m_DeviceInfo.Version = version;

		GR_CORE_INFO("VENDOR   : {0}", m_DeviceInfo.Vendor);
		GR_CORE_INFO("RENDERER : {0}", m_DeviceInfo.Renderer);
		GR_CORE_INFO("API      : {0}", m_DeviceInfo.API);
		GR_CORE_INFO("VERSION  : {0}", m_DeviceInfo.Version);
	}
}