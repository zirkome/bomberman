#ifndef _THREAD_H_
# define _THREAD_H_

# include "IThread.hpp"

/*
 * Posix Thread C++ Encapsulation
 */
class PThread : public IThread
{
private:
  Func _task;
  void *_arg;
  pthread_t _thread;

public:
  explicit PThread(Func f, void *arg);
  virtual ~PThread();

public:
  virtual void start();
  virtual void join(void **retval);
  virtual void cancel() const;

  void setCancelModeAsynchronous() const;
};

#endif /* _THREAD_H_ */
