#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Glacier 
{
	/*
	*   <Log>
	*   spdlog ���̺귯���� ����Ͽ� �����ϰ� �ܼ� â�� ����� �� �ֵ��� �ϴ� Ŭ����.
	*/
	class GLACIER_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;    // static��� ������ Ŭ���� ������ ���� �����ϰ� ���Ǵ� �Ұ���.
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// core log ��ũ��
#define GR_CORE_TRACE(...)	::Glacier::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define GR_CORE_INFO(...)	::Glacier::Log::GetCoreLogger()->info(__VA_ARGS__)
#define GR_CORE_WARN(...)	::Glacier::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define GR_CORE_ERROR(...)	::Glacier::Log::GetCoreLogger()->error(__VA_ARGS__)
#define GR_CORE_FATAL(...)	::Glacier::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// client log ��ũ��
#define GR_TRACE(...)		::Glacier::Log::GetClientLogger()->trace(__VA_ARGS__)
#define GR_INFO(...)		::Glacier::Log::GetClientLogger()->info(__VA_ARGS__)
#define GR_WARN(...)		::Glacier::Log::GetClientLogger()->warn(__VA_ARGS__)
#define GR_ERROR(...)		::Glacier::Log::GetClientLogger()->error(__VA_ARGS__)
#define GR_FATAL(...)		::Glacier::Log::GetClientLogger()->fatal(__VA_ARGS__)