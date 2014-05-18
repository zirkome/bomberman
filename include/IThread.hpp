#ifndef _ITHREAD_H_
# define _ITHREAD_H_

typedef void *(*Func)(void *);

/*
 * Generic Thread interface
 */
class IThread
{
public:
  virtual ~IThread() {};

public:
  virtual void start() = 0;
  virtual void join(void** retval) = 0;
  virtual void cancel() const = 0;
};

#endif /* _ITHREAD_H_ */
