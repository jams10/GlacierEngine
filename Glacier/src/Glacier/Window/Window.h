#pragma once

#include "pch.h"

#include "Glacier/Core.h"
#include "Glacier/Utils/CustomDelegate.h"

namespace Glacier
{
	using std::wstring;
	struct WindowInfo
	{
		wstring Title;
		uint16 Width;
		uint16 Height;

		WindowInfo(wstring title = L"Glacier", uint16 width = 1280, uint16 height = 720)
			: Title(title), Width(width), Height(height)
		{}
	};

	/*
	*   <Window>
	*   윈도우를 추상화 한 추상 클래스(인터페이스 클래스).
	*   플랫폼 별로 이를 구체화 하여 실제 윈도우 클래스를 만들어줌.
	*/
	class GLACIER_API Window
	{
	public:
		virtual ~Window() {}

		virtual int OnUpdate() = 0;

		virtual uint16 GetWidth() const = 0;
		virtual uint16 GetHeight() const = 0;

		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;
		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowInfo& infos = WindowInfo());
	};
}