#include "pch.h"

// 함수 구현부가 들어 있는 cpp 파일도 같이 컴파일 되도록 만들어줌. 아니면 함수 구현부를 찾지 못해 LINK external symbol 에러가 일어남.
#include "imgui.cpp"
#include "imgui_demo.cpp"
#include "imgui_draw.cpp"
#include "imgui_tables.cpp"
#include "imgui_widgets.cpp"
#include "backends/imgui_impl_dx11.cpp"
#include "backends/imgui_impl_win32.cpp"