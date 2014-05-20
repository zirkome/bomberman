#include <iostream>
#include <stdexcept>
#include <string>
#include <cstring>
#include <cerrno>

#include "PThread.hpp"

PThread::PThread(Func f, void *arg)
  : _task(f), _arg(arg)
{
}

PThread::~PThread()
{
  join(NULL);
}

void PThread::start()
{
  if (pthread_create(&_thread, NULL, _task, _arg) != 0)
    throw std::runtime_error(std::string("pthread_create") + strerror(errno));
}

void PThread::join(void **retval)
{
  if (pthread_join(_thread, retval) != 0)
    throw std::runtime_error(std::string("pthread_join") + strerror(errno));
}

void PThread::setCancelModeAsynchronous() const
{
  if (pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, 0) != 0)
    throw std::runtime_error(std::string("pthread_setcanceltype") + strerror(errno));
  if (pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, 0) != 0)
    throw std::runtime_error(std::string("pthread_setcancelstate") + strerror(errno));
}

void PThread::cancel() const
{
  if (pthread_cancel(_thread) != 0)
    throw std::runtime_error(std::string("pthread_cancel") + strerror(errno));
}

