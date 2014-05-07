#ifndef _ICONDVAR_H_
# define _ICONDVAR_H_

class ICondVar
{
public:
  virtual ~ICondVar() {}

public:
  virtual void wait() = 0;
  virtual void wait(long timeout) = 0;
  virtual void notify() = 0;
  virtual void notifyAll() = 0;
};

#endif /* _ICONDVAR_H_ */
