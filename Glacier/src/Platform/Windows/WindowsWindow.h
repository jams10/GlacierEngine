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
		WindowsWindow(const EventCallbackFn& callback, const WindowInfo& info);
		virtual ~WindowsWindow();

		virtual int OnUpdate();

		virtual uint16 GetWidth() const override { return m_Data.Width; }
		virtual uint16 GetHeight() const override { return m_Data.Height; }

		// 이벤트 콜백 함수 설정. Application 쪽에서 호출해 윈도우에서 이벤트 발생 시 호출할 콜백 함수를 바인딩 해줌.
		inline virtual void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		virtual void SetVSync(bool enabled) override {}
		virtual bool IsVSync() const override { return true; }
		virtual void* GetNativeWindow() const override { return m_HWnd; }

		static int ProcessMessages(); // 모든 윈도우에 대한 메시지를 처리해야 하므로 static으로 선언함.

		void Initialize(const wchar_t* name, int width, int height);
	private:
		void SetTitle(const wstring& title);

		static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	private:
		HWND m_HWnd;

		// 윈도우 이벤트 발생 시 
		struct WindowData 
		{
			std::string Title;
			uint16 Width, Height;
			bool VSync;

			EventCallbackFn EventCallback; // 이벤트 콜백 함수. Application의 ProcessEvent를 호출하게 됨.
		};

		WindowData m_Data;
	};
}