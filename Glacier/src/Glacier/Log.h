#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Glacier 
{
	/*
	*   <Log>
	*   spdlog 라이브러리를 사용하여 간편하게 콘솔 창에 기록할 수 있도록 하는 클래스.
	*/
	class GLACIER_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;    // static멤버 변수는 클래스 내에서 선언만 가능하고 정의는 불가능.
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// core log 매크로
#define GR_CORE_TRACE(...)	::Glacier::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define GR_CORE_INFO(...)	::Glacier::Log::GetCoreLogger()->info(__VA_ARGS__)
#define GR_CORE_WARN(...)	::Glacier::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define GR_CORE_ERROR(...)	::Glacier::Log::GetCoreLogger()->error(__VA_ARGS__)
#define GR_CORE_FATAL(...)	::Glacier::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// client log 매크로
#define GR_TRACE(...)		::Glacier::Log::GetClientLogger()->trace(__VA_ARGS__)
#define GR_INFO(...)		::Glacier::Log::GetClientLogger()->info(__VA_ARGS__)
#define GR_WARN(...)		::Glacier::Log::GetClientLogger()->warn(__VA_ARGS__)
#define GR_ERROR(...)		::Glacier::Log::GetClientLogger()->error(__VA_ARGS__)
#define GR_FATAL(...)		::Glacier::Log::GetClientLogger()->fatal(__VA_ARGS__)