#ifndef _PCONDVAR_H_
# define _PCONDVAR_H_

# include <pthread.h>

# include "ICondVar.hpp"
# include "PMutex.hpp"

class PCondVar : public ICondVar
{
private:
  pthread_cond_t _cv;
  PMutex& _mutex;

public:
  static const long kInfinite = -1;

public:
  explicit PCondVar(IMutex& mutex);
  virtual ~PCondVar();

public:
  virtual void wait();
  virtual void wait(long timeout);
  virtual void notify();
  virtual void notifyAll();
};

#endif /* _PCONDVAR_H_ */
