#pragma once

#include "Glacier/Core/Core.h"

#include <chrono>

namespace Glacier
{
	class GLACIER_API GameTimer
	{
	public:
		GameTimer();

		float GetTotalTime();
		float GetDeltaTime();

		void ReStartTotalTimer();
		void PauseTotalTimer();
		void Tick();

		bool IsStopped() { return hasStopped; }

	private:
		bool hasStopped;
		float pausedTime;
		std::chrono::steady_clock::time_point initialTimePoint; // �ʱ� Timer ��ü ���� ������ Time Point
		std::chrono::steady_clock::time_point startTimePoint;   // ��ü Ÿ�̸� ���� ���� Time Point
		std::chrono::steady_clock::time_point stopTimePoint;    // ��ü Ÿ�̸� ���� ���� Time Point
		std::chrono::steady_clock::time_point prevTimePoint;    // ���� ������ ���� Time Point
		std::chrono::steady_clock::time_point currentTimePoint; // ���� ������ ���� Time Point
	};
}