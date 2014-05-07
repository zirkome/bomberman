#include "PCondVar.hpp"

PCondVar::PCondVar(IMutex& mtx) : _mutex(dynamic_cast<PMutex&>(mtx))
{
  pthread_cond_init(&_cv, NULL);
}

PCondVar::~PCondVar()
{
  pthread_cond_destroy(&_cv);
}

void PCondVar::notify()
{
  pthread_cond_signal(&_cv);
}

void PCondVar::notifyAll()
{
  pthread_cond_broadcast(&_cv);
}

void PCondVar::wait()
{
  wait(kInfinite);
}

void PCondVar::wait(long timeout)
{
  if (timeout == kInfinite)
    {
      pthread_cond_wait(&_cv, &_mutex.mutex);
    }
  else
    {
      timespec ts;
      clock_gettime(CLOCK_REALTIME, &ts);
      ts.tv_sec += timeout / 1000;
      ts.tv_nsec += timeout % 1000 * 1000;
      pthread_cond_timedwait(&_cv, &_mutex.mutex, &ts);
    }
}
