#include "pch.h"
#include "WindowsInput.h"

#include "Glacier/Application.h"

namespace Glacier
{
	// static 멤버 변수의 경우 클래스의 모든 객체들이 공유. 클래스의 인스턴스와 무관하게 클래스 자체에 속함.
	// 접근 지정자는 클래스의 인스턴스에 적용되는 규칙이기 때문에 정적 멤버 변수에는 적용되지 않음.
	// 따라서 private static 멤버 변수를 자식 클래스에서는 접근이 가능하지만, 외부에서는 접근이 불가능.
	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		SHORT state = GetKeyState(keycode);
		return state & 0xf000;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		SHORT state = GetKeyState(button);
		return state & 0xf000;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		POINT mousePos;
		BOOL result = GetCursorPos(&mousePos);
		if (!result)
		{
			GR_CORE_ERROR("Failed : Can't get curosr pos!");
		}
		ScreenToClient(static_cast<HWND>(Application::Get().GetWindow().GetNativeWindow()), &mousePos);

		return std::pair<float, float>(mousePos.x, mousePos.y);
	}

	float WindowsInput::GetMouseXImpl()
	{
		auto [x, y] = GetMousePositionImpl(); // C++17 부터 이렇게 입력을 한 번에 받아올 수 있음.
		return x;
	}

	float WindowsInput::GetMouseYImpl()
	{
		auto [x, y] = GetMousePositionImpl(); 
		return y;
	}

}