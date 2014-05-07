#ifndef _IMUTEX_H_
# define _IMUTEX_H_

class IMutex
{
public:
  virtual ~IMutex() {};

public:
  virtual void lock() = 0;
  virtual void unlock() = 0;
  virtual void trylock() = 0;
};

#endif /* _IMUTEX_H_ */
