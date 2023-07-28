#include "pch.h"
#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Glacier
{
	// static Ÿ�� �ΰ� ��ü ���� �� �ʱ�ȭ.
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$"); // �α� ������ ����.
		s_CoreLogger = spdlog::stdout_color_mt("GLACIER");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}

/*
	<static ��� ����>
	static ��� ������ ��� ��ü���� ������ �� �־�� ��.
	��, ���α׷� ���ۺ��� ������ �����Ǿ�� �ϱ� ������ ���� ���� ������ ����(�ʱ�ȭ)�� �� ����.

	static ��� ������ �ʱ�ȭ�� ��� ���Ͽ��� �Ұ��� ��.
	��� ���Ͽ� static ��� ������ ������ ������, ���� ������ ��� ������ include�� �� ���� static ��� ������ ������ ���� �� �ʱ�ȭ �ϴ°��� �Ǳ� ����.
*/