#include <stdexcept>

#include "PMutex.hpp"

PMutex::PMutex(const pthread_mutexattr_t *attr)
{
  if (pthread_mutex_init(&mutex, attr) != 0)
    throw std::runtime_error("pthread_mutex_init");
}

PMutex::~PMutex()
{
  if (pthread_mutex_destroy(&mutex) != 0)
    throw std::runtime_error("pthread_mutex_destroy");
}

void PMutex::lock()
{
  if (pthread_mutex_lock(&mutex) != 0)
    throw std::runtime_error("pthread_mutex_lock");
}

void PMutex::unlock()
{
  if (pthread_mutex_unlock(&mutex) != 0)
    throw std::runtime_error("pthread_mutex_unlock");
}

void PMutex::trylock()
{
  if (pthread_mutex_trylock(&mutex) != 0)
    throw std::runtime_error("pthread_mutex_trylock");
}
