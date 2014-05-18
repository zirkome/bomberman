#ifndef _SCOPELOCK_H_
# define _SCOPELOCK_H_

# include <pthread.h>

# include "IMutex.hpp"

class ScopeLock
{
public:
  ScopeLock(IMutex& mutex);
  virtual ~ScopeLock();

private:
  IMutex& _mutex;
};

#endif /* _SCOPELOCK_H_ */
