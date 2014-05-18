#include "ScopeLock.hpp"

ScopeLock::ScopeLock(IMutex& mtx)
  : _mutex(mtx)
{
  _mutex.lock();
}

ScopeLock::~ScopeLock()
{
  _mutex.unlock();
}
