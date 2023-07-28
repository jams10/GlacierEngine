#pragma once

#include "Glacier/Window/Window.h"
#include "WindowsHeaders.h"

namespace Glacier
{
	using std::wstring;

	class WindowsWindow : public Window
	{
#pragma region WindowClass
	private:
		// 윈도우 클래스를 등록/해제를 관리하는 싱글톤.
		class WindowClass
		{
		public:
			static const wchar_t* GetName();
			static HINSTANCE GetInstance();
		private:
			WindowClass();
			~WindowClass();
			WindowClass(const WindowClass&) = delete;
			WindowClass& operator=(const WindowClass&) = delete;

			static constexpr const wchar_t* wndClassName = L"WindowClass";
			static WindowClass wndClass; // SINGLETON
			HINSTANCE hInst;
		};
#pragma endregion
	public:
		WindowsWindow(const WindowInfo& info);
		virtual ~WindowsWindow();

		virtual int OnUpdate();

		virtual uint16 GetWidth() const override { return m_Width; }
		virtual uint16 GetHeight() const override { return m_Height; }

		virtual void SetVSync(bool enabled) override {}
		virtual bool IsVSync() const override { return true; }
		virtual void* GetNativeWindow() const override { return m_HWnd; }

		static int ProcessMessages(); // 모든 윈도우에 대한 메시지를 처리해야 하므로 static으로 선언함.

	private:
		void Initialize(const wchar_t* name, int width, int height);
		void SetTitle(const wstring& title);

		static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	private:
		uint16 m_Width;
		uint16 m_Height;
		HWND m_HWnd;
	};
}