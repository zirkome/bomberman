#include "Timer.hpp"
#include <iostream>

Timer::Timer(double time) : _time(time)
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
