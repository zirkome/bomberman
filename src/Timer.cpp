#include "Timer.hpp"
#include <iostream>

Timer::Timer(double time) : _time(time), _startTime(time)
{
}

Timer::~Timer()
{

}

bool Timer::update(double clock)
{
  _time -= clock;
  if (_time < 0)
    return true;
  return false;
}

void Timer::reset(double time)
{
  _time = time;
}

double Timer::getTime() const
{
  return _startTime;
}

void	Timer::addTime(double time)
{
  _time += time;
}

double Timer::getRemainingTime() const
{
  return _time;
}
