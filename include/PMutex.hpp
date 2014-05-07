#ifndef _MUTEX_H_
# define _MUTEX_H_

# include <pthread.h>

# include "IMutex.hpp"

/*
 * Posix Mutex C++ encapsulation
 */
class PMutex : public IMutex
{
public:
  pthread_mutex_t mutex;

public:
  PMutex(const pthread_mutexattr_t *attr = NULL);
  virtual ~PMutex();

public:
  virtual void lock();
  virtual void unlock();
  virtual void trylock();
};

#endif /* _MUTEX_H_ */
