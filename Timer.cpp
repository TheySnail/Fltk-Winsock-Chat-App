#include "Timer.h"

#include <FL/Fl.H>

Timer::Timer(double _duration)
	: m_duration(_duration)
{
	//Fl::add_timeout(_duration, tick, this);
}
Timer::~Timer()
{
	Fl::remove_timeout(tick, this);
}

void Timer::tick(void* _userdata)
{
	Timer* self = (Timer*)_userdata;

	self->on_tick();
	Fl::repeat_timeout(self->m_duration, tick, _userdata);
}

void Timer::StartTimer()
{
	Fl::add_timeout(m_duration, tick, this);
}

void Timer::on_tick() { }