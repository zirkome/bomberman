#include "Timer.hpp"

Timer::Timer(float time) : _time(time)
{

}

Timer::~Timer()
{

}

bool Timer::update(gdl::Clock const &clock)
{
  _time -= clock.getElapsed();
  if (_time < 0)
    return true;
  return false;
}

void Timer::reset(float time)
{
  _time = time;
}
