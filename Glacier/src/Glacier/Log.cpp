#include "pch.h"
#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Glacier
{
	// static 타입 로거 객체 정의 및 초기화.
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$"); // 로그 패턴을 설정.
		s_CoreLogger = spdlog::stdout_color_mt("GLACIER");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}

/*
	<static 멤버 변수>
	static 멤버 변수는 모든 객체들이 접근할 수 있어야 함.
	즉, 프로그램 시작부터 끝까지 유지되어야 하기 때문에 전역 범위 에서만 정의(초기화)할 수 있음.

	static 멤버 변수의 초기화는 헤더 파일에선 불가능 함.
	헤더 파일에 static 멤버 변수를 정의해 버리면, 여러 곳에서 헤더 파일을 include할 때 마다 static 멤버 변수를 여러번 정의 및 초기화 하는것이 되기 때문.
*/