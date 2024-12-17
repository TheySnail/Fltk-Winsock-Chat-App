#pragma once

struct Timer
{
	Timer(double _duration);
	virtual ~Timer();
	virtual void on_tick();
	virtual void StartTimer();
private:
	double m_Duration;
	static void tick(void* _userdata);
};