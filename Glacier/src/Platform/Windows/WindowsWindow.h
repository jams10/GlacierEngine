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
		// ������ Ŭ������ ���/������ �����ϴ� �̱���.
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

		// �̺�Ʈ �ݹ� �Լ� ����. Application �ʿ��� ȣ���� �����쿡�� �̺�Ʈ �߻� �� ȣ���� �ݹ� �Լ��� ���ε� ����.
		inline virtual void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		virtual void SetVSync(bool enabled) override {}
		virtual bool IsVSync() const override { return true; }
		virtual void* GetNativeWindow() const override { return m_HWnd; }

		static int ProcessMessages(); // ��� �����쿡 ���� �޽����� ó���ؾ� �ϹǷ� static���� ������.

		void Initialize(const wchar_t* name, int width, int height);
	private:
		void SetTitle(const wstring& title);

		static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	private:
		HWND m_HWnd;

		// ������ �̺�Ʈ �߻� �� 
		struct WindowData 
		{
			std::string Title;
			uint16 Width, Height;
			bool VSync;

			EventCallbackFn EventCallback; // �̺�Ʈ �ݹ� �Լ�. Application�� ProcessEvent�� ȣ���ϰ� ��.
		};

		WindowData m_Data;
	};
}