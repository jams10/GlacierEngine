#include "pch.h"
#include "WindowsWindow.h"

#include "Glacier/Utils/StringEncode.h"
#include "Glacier/Event/ApplicationEvent.h"
#include "Glacier/Event/KeyboardEvent.h"
#include "Glacier/Event/MouseEvent.h"

#include "Platform/DirectX/DirectX11Common.h"
#include "Platform/DirectX/DirectX11Manager.h"

#include "backends/imgui_impl_win32.h"

// imgui_impl_win32.cpp에 정의된 메시지 처리 함수에 대한 전방 선언
// VCPKG를 통해 IMGUI를 사용할 경우 빨간줄로 경고가 뜰 수 있음
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam);

namespace Glacier
{
#pragma region WindowClass
	// 윈도우 클래스
	WindowsWindow::WindowClass WindowsWindow::WindowClass::wndClass; // static 멤버 변수 정의
	// WindowClass 생성자. 윈도우 클래스 생성을 담당.
	WindowsWindow::WindowClass::WindowClass()
		:
		hInst(GetModuleHandle(nullptr)) // exe 파일에서는 이 함수로 얻어오는 인스턴스 핸들이나 WinMain()의 매개변수인 hInstance의 값이 다르지 않다. 
		// 그러나, DLL 안에 윈도우들을 생성할 경우 WinMain의 hInstance는 DLL의 hInstance를, GetModuleHandle은 여전히 DLL을 로드한 exe 파일의 HINSTANCE를 반환 한다.
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
	// WindowClass 소멸자. 등록한 윈도우 해제 담당.
	WindowsWindow::WindowClass::~WindowClass()
	{
		UnregisterClass(wndClassName, GetInstance()); // 등록한 윈도우를 해제 해줌.
	}
	// 윈도우 클래스의 이름을 리턴해주는 함수.
	const wchar_t* WindowsWindow::WindowClass::GetName()
	{
		return wndClassName;
	}
	// 프로그램 인스턴스에 대한 핸들을 리턴해주는 함수.
	HINSTANCE WindowsWindow::WindowClass::GetInstance()
	{
		return wndClass.hInst;
	}
#pragma endregion

	Window* Window::Create(const EventCallbackFn& callback, const WindowInfo& info) // Window 클래스에서 만들어준 static 함수를 플랫폼별로(여기서는 windows) 구현해줌.
	{
		return new WindowsWindow(callback, info);
	}

	// Window 클래스 생성자. 윈도우 생성 및 설정
	WindowsWindow::WindowsWindow(const EventCallbackFn& callback, const WindowInfo& info)
		:
		m_HWnd(nullptr)
	{
		m_Data.EventCallback = callback;
		Initialize(info.Title.c_str(), info.Width, info.Height);
	}

	// Window 클래스 소멸자. 생성한 윈도우 파괴.
	WindowsWindow::~WindowsWindow()
	{
		GR_CORE_WARN("Destroy Windows window!");
		DestroyWindow(m_HWnd);
	}

	void WindowsWindow::OnUpdate()
	{
		ProcessMessages();
		m_GraphicsManager->SwapBuffers();
	}

	void WindowsWindow::Initialize(const wchar_t* name, int width, int height)
	{
		// 우리가 원하는 그림이 그려질 부분의 해상도
		RECT wr = { 0, 0, width, height };

		// 윈도우 사이즈 조절.
		if (!AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE))
		{
			GR_CORE_ERROR("Failed : AdjustWindowRect");
			return;
		}

		// 윈도우를 생성하고 윈도우에 대한 핸들을 얻어옴.
		m_HWnd = CreateWindow(
			WindowClass::GetName(), name,
			WS_OVERLAPPEDWINDOW,
			100, 100, wr.right - wr.left, wr.bottom - wr.top,
			nullptr, nullptr, WindowClass::GetInstance(), this
		);

		// 윈도우 생성에 실패한 경우
		if (m_HWnd == nullptr)
		{
			GR_CORE_ERROR("Failed : Create WindowsWindow");
			return;
		}

		// 윈도우 화면에 띄우기.
		ShowWindow(m_HWnd, SW_SHOWDEFAULT);
		UpdateWindow(m_HWnd); // WPAINT 메시지가 있다면 즉시 화면 갱신.

		// 콘솔창이 렌더링 창을 덮는 것을 방지.
		SetForegroundWindow(m_HWnd);

		GR_CORE_WARN("Initialized WindowsWindow successfully!");

		m_GraphicsManager = new DirectX11Manager(m_HWnd);
		m_GraphicsManager->Init();

		// PipelineState 초기화.
		Glacier::InitCommonStates();

		return;
	}

	// 윈도우 타이틀 이름 변경해주는 함수.
	void WindowsWindow::SetTitle(const std::wstring& title)
	{
		if (SetWindowText(m_HWnd, title.c_str()) == 0)
		{
			GR_CORE_ERROR("Failed : Set WindowsWindow Title.");
			return;
		}
	}

	// 윈도우 메시지 루프. 윈도우 메시지를 프로시져로 보내주는 함수.
	int WindowsWindow::ProcessMessages()
	{
		MSG msg{ 0 };

		// 메시지 큐에 메시지가 있으면, 해당 메시지를 제거하고 프로시져로 보내줌.(큐가 비어있어도 블록 상태에 들어가지 않음.)
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

	// 직접 만들어준 멤버 함수를 윈도우 프로시져로 사용하기 위한 기본 설정을 담당하는 함수.
	LRESULT CALLBACK WindowsWindow::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		// CreateWindow()의 마지막 인자로 넘겨준 this 포인터를 이용해 윈도우 API 쪽에있는 윈도우 클래스 포인터를 저장함.
		if (msg == WM_NCCREATE)
		{
			// 생성 데이터로 부터 윈도우 클래스에 대한 포인터를 추출.
			const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
			WindowsWindow* const pWnd = static_cast<WindowsWindow*>(pCreate->lpCreateParams);

			// WinAPI에 의해 관리되는 사용자 데이터를 윈도우 클래스에 대한 포인터를 저장하도록 설정함.
			SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));

			// 메시지 프로시져를 일반 핸들러로 변경하고 메시지를 받아들일 준비를 함.
			SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&WindowsWindow::HandleMsgThunk));

			// window class 핸들러에 메시지를 전달함.
			return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
		}

		// WN_NCCREATE 메시지 전에 메시지를 받는다면, 일반 핸들러로 메시지를 처리.
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	// 윈도우 메시지를 우리가 작성한 멤버 함수로 전달하기 위한 함수.
	LRESULT CALLBACK WindowsWindow::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		// window class에 대한 포인터를 얻어옴.
		WindowsWindow* const pWnd = reinterpret_cast<WindowsWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

		// window class 핸들러에 메시지를 전달함.
		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
	}

	// 실제 윈도우 메시지를 처리해 줄 함수.
	LRESULT WindowsWindow::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		// ImGui에 대한 입력인 경우 ImGui가 consume.
		if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
			return true;

		WindowsWindow* const pWnd = reinterpret_cast<WindowsWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

		switch (msg)
		{
		case WM_SIZE:
		{
			pWnd->m_Data.Width = uint32(LOWORD(lParam));
			pWnd->m_Data.Height = uint32(HIWORD(lParam));

			WindowResizeEvent event(pWnd->m_Data.Width, pWnd->m_Data.Height);
			pWnd->m_Data.EventCallback(event);
		}
			break;
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		{
			if (lParam & 0x40000000) // 이전에도 키를 누른 경우.
			{
				KeyPressedEvent event(static_cast<int>(wParam), 1);
				pWnd->m_Data.EventCallback(event);
			}
			else
			{
				KeyPressedEvent event(static_cast<int>(wParam), 0);
				pWnd->m_Data.EventCallback(event);
			}
		}
			break;
		case WM_KEYUP:
		case WM_SYSKEYUP:
		{
			KeyReleasedEvent event(static_cast<int>(wParam));
			pWnd->m_Data.EventCallback(event);
		}
			break;
		case WM_MOUSEMOVE:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(wParam);
			ScreenToClient(hWnd, &pt);

			MouseMovedEvent event(static_cast<float>(pt.x), static_cast<float>(pt.y));
			pWnd->m_Data.EventCallback(event);
		}
			break;
		case WM_LBUTTONDOWN:
		{
			MouseButtonPressedEvent event(static_cast<int>(VK_LBUTTON));
			pWnd->m_Data.EventCallback(event);
		}
			break;
		case WM_RBUTTONDOWN:
		{
			MouseButtonPressedEvent event(static_cast<int>(VK_RBUTTON));
			pWnd->m_Data.EventCallback(event);
		}
			break;
		case WM_LBUTTONUP:
		{
			MouseButtonReleasedEvent event(static_cast<int>(VK_LBUTTON));
			pWnd->m_Data.EventCallback(event);
		}
			break;
		case WM_RBUTTONUP:
		{
			MouseButtonReleasedEvent event(static_cast<int>(VK_RBUTTON));
			pWnd->m_Data.EventCallback(event);
		}
			break;
		case WM_MOUSEWHEEL:
		{
			const POINTS pt = MAKEPOINTS(lParam);
			const int delta = GET_WHEEL_DELTA_WPARAM(wParam);

			uint16 offsetX = static_cast<uint16>(pt.x);
			uint16 offsetY = static_cast<uint16>(pt.y);

			if (delta >= 0)
			{
				MouseWheelUpEvent event(offsetX, offsetY);
				pWnd->m_Data.EventCallback(event);
			}
			else if (delta <= -WHEEL_DELTA)
			{
				MouseWheelDownEvent event(offsetX, offsetY);
				pWnd->m_Data.EventCallback(event);
			}
		}
			break;
		case WM_DESTROY:
			//PostQuitMessage(0);

			WindowCloseEvent event;
			pWnd->m_Data.EventCallback(event);
			return 0;
		}

		return ::DefWindowProc(hWnd, msg, wParam, lParam);
	}
}