#include "pch.h"
#include "WindowsWindow.h"

#include "Glacier/Utils/StringEncode.h"

#include "backends/imgui_impl_win32.h"

// imgui_impl_win32.cpp�� ���ǵ� �޽��� ó�� �Լ��� ���� ���� ����
// VCPKG�� ���� IMGUI�� ����� ��� �����ٷ� ��� �� �� ����
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam);

namespace Glacier
{
#pragma region WindowClass
	// ������ Ŭ����
	WindowsWindow::WindowClass WindowsWindow::WindowClass::wndClass; // static ��� ���� ����
	// WindowClass ������. ������ Ŭ���� ������ ���.
	WindowsWindow::WindowClass::WindowClass()
		:
		hInst(GetModuleHandle(nullptr)) // exe ���Ͽ����� �� �Լ��� ������ �ν��Ͻ� �ڵ��̳� WinMain()�� �Ű������� hInstance�� ���� �ٸ��� �ʴ�. 
		// �׷���, DLL �ȿ� ��������� ������ ��� WinMain�� hInstance�� DLL�� hInstance��, GetModuleHandle�� ������ DLL�� �ε��� exe ������ HINSTANCE�� ��ȯ �Ѵ�.
	{
		WNDCLASSEX wc = { 0 };
		wc.cbSize = sizeof(wc);
		wc.style = CS_OWNDC;
		wc.lpfnWndProc = HandleMsgSetup;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = GetInstance();
		wc.hIcon = nullptr;
		wc.hCursor = nullptr;
		wc.hbrBackground = nullptr;
		wc.lpszMenuName = nullptr;
		wc.lpszClassName = GetName();
		wc.hIconSm = nullptr;

		RegisterClassEx(&wc);
	}
	// WindowClass �Ҹ���. ����� ������ ���� ���.
	WindowsWindow::WindowClass::~WindowClass()
	{
		UnregisterClass(wndClassName, GetInstance()); // ����� �����츦 ���� ����.
	}
	// ������ Ŭ������ �̸��� �������ִ� �Լ�.
	const wchar_t* WindowsWindow::WindowClass::GetName()
	{
		return wndClassName;
	}
	// ���α׷� �ν��Ͻ��� ���� �ڵ��� �������ִ� �Լ�.
	HINSTANCE WindowsWindow::WindowClass::GetInstance()
	{
		return wndClass.hInst;
	}
#pragma endregion

	Window* Window::Create(const WindowInfo& info) // Window Ŭ�������� ������� static �Լ��� �÷�������(���⼭�� windows) ��������.
	{
		return new WindowsWindow(info);
	}

	// Window Ŭ���� ������. ������ ���� �� ����
	WindowsWindow::WindowsWindow(const WindowInfo& info)
		:
		m_Width(0),
		m_Height(0),
		m_HWnd(nullptr)
	{
		Initialize(info.Title.c_str(), info.Width, info.Height);
	}

	// Window Ŭ���� �Ҹ���. ������ ������ �ı�.
	WindowsWindow::~WindowsWindow()
	{
		GR_CORE_TRACE("Destroy Windows window.");
		DestroyWindow(m_HWnd);
	}

	int WindowsWindow::OnUpdate()
	{
		return ProcessMessages();
	}

	void WindowsWindow::Initialize(const wchar_t* name, int width, int height)
	{
		// �츮�� ���ϴ� �׸��� �׷��� �κ��� �ػ�
		RECT wr = { 0, 0, width, height };

		// ������ ������ ����.
		if (!AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE))
		{
			GR_CORE_ERROR("Failed : AdjustWindowRect");
			return;
		}

		// �����츦 �����ϰ� �����쿡 ���� �ڵ��� ����.
		m_HWnd = CreateWindow(
			WindowClass::GetName(), name,
			WS_OVERLAPPEDWINDOW,
			100, 100, wr.right - wr.left, wr.bottom - wr.top,
			nullptr, nullptr, WindowClass::GetInstance(), this
		);

		// ������ ������ ������ ���
		if (m_HWnd == nullptr)
		{
			GR_CORE_ERROR("Failed : Create WindowsWindow");
			return;
		}

		//// Imgui Win32 ���� �ʱ�ȭ.
		//if (ImGui_ImplWin32_Init(m_HWnd) == false)
		//{
		//	GR_CORE_ERROR("Failed : ImGui_ImplWin32_Init()");
		//	return;
		//}

		// ������ ȭ�鿡 ����.
		ShowWindow(m_HWnd, SW_SHOWDEFAULT);
		UpdateWindow(m_HWnd); // WPAINT �޽����� �ִٸ� ��� ȭ�� ����.

		// �ܼ�â�� ������ â�� ���� ���� ����.
		SetForegroundWindow(m_HWnd);

		GR_CORE_TRACE("Initialized WindowsWindow successfully!");
		return;
	}

	// ������ Ÿ��Ʋ �̸� �������ִ� �Լ�.
	void WindowsWindow::SetTitle(const std::wstring& title)
	{
		if (SetWindowText(m_HWnd, title.c_str()) == 0)
		{
			GR_CORE_ERROR("Failed : Set WindowsWindow Title.");
			return;
		}
	}

	// ������ �޽��� ����. ������ �޽����� ���ν����� �����ִ� �Լ�.
	int WindowsWindow::ProcessMessages()
	{
		MSG msg{ 0 };

		// �޽��� ť�� �޽����� ������, �ش� �޽����� �����ϰ� ���ν����� ������.(ť�� ����־ ��� ���¿� ���� ����.)
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				return 0;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		return 1;
	}

	// ���� ������� ��� �Լ��� ������ ���ν����� ����ϱ� ���� �⺻ ������ ����ϴ� �Լ�.
	LRESULT CALLBACK WindowsWindow::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		// CreateWindow()�� ������ ���ڷ� �Ѱ��� this �����͸� �̿��� ������ API �ʿ��ִ� ������ Ŭ���� �����͸� ������.
		if (msg == WM_NCCREATE)
		{
			// ���� �����ͷ� ���� ������ Ŭ������ ���� �����͸� ����.
			const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
			WindowsWindow* const pWnd = static_cast<WindowsWindow*>(pCreate->lpCreateParams);

			// WinAPI�� ���� �����Ǵ� ����� �����͸� ������ Ŭ������ ���� �����͸� �����ϵ��� ������.
			SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));

			// �޽��� ���ν����� �Ϲ� �ڵ鷯�� �����ϰ� �޽����� �޾Ƶ��� �غ� ��.
			SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&WindowsWindow::HandleMsgThunk));

			// window class �ڵ鷯�� �޽����� ������.
			return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
		}

		// WN_NCCREATE �޽��� ���� �޽����� �޴´ٸ�, �Ϲ� �ڵ鷯�� �޽����� ó��.
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	// ������ �޽����� �츮�� �ۼ��� ��� �Լ��� �����ϱ� ���� �Լ�.
	LRESULT CALLBACK WindowsWindow::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		// window class�� ���� �����͸� ����.
		WindowsWindow* const pWnd = reinterpret_cast<WindowsWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

		// window class �ڵ鷯�� �޽����� ������.
		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
	}

	// ���� ������ �޽����� ó���� �� �Լ�.
	LRESULT WindowsWindow::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		// ImGui�� ���� �Է��� ��� ImGui�� consume.
		if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
			return true;

		switch (msg)
		{
		case WM_SIZE:
			m_Width = uint32(LOWORD(lParam));
			m_Height = uint32(HIWORD(lParam));

			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		}

		return ::DefWindowProc(hWnd, msg, wParam, lParam);
	}
}