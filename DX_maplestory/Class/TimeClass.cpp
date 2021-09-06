#include "../Header/stdafx.h"
#include "TimeClass.h"

TimeClass::TimeClass()
{
}

TimeClass::~TimeClass()
{
}

bool TimeClass::Initialize()
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_frequency);
	if (!m_frequency)
	{
		return false;
	}

	m_ticksPerMS = (float)(m_frequency / 1000);
	QueryPerformanceCounter((LARGE_INTEGER*)&m_startTime);

	return true;
}

void TimeClass::Frame()
{
	INT64 currentTime = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
	
	float timeDifference = (float)(currentTime - m_startTime);
	m_frameTime = timeDifference / m_ticksPerMS;
	
	m_startTime = currentTime;
}

float TimeClass::GetTime()
{
	return m_frameTime;
}