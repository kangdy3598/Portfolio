#pragma once

class TimeClass
{
public :
	TimeClass();
	~TimeClass();

	bool Initialize();
	void Frame();

	float GetTime();

private:
	INT64 m_frequency = 0;
	float m_ticksPerMS = 0;
	INT64 m_startTime = 0;
	float m_frameTime = 0;
};