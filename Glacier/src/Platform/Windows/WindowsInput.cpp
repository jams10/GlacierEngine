#include "pch.h"
#include "WindowsInput.h"

#include "Glacier/Application.h"

namespace Glacier
{
	// static ��� ������ ��� Ŭ������ ��� ��ü���� ����. Ŭ������ �ν��Ͻ��� �����ϰ� Ŭ���� ��ü�� ����.
	// ���� �����ڴ� Ŭ������ �ν��Ͻ��� ����Ǵ� ��Ģ�̱� ������ ���� ��� �������� ������� ����.
	// ���� private static ��� ������ �ڽ� Ŭ���������� ������ ����������, �ܺο����� ������ �Ұ���.
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
		auto [x, y] = GetMousePositionImpl(); // C++17 ���� �̷��� �Է��� �� ���� �޾ƿ� �� ����.
		return x;
	}

	float WindowsInput::GetMouseYImpl()
	{
		auto [x, y] = GetMousePositionImpl(); 
		return y;
	}

}