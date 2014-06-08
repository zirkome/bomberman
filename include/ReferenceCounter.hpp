#ifndef _REFERENCECOUNTER_H_
# define _REFERENCECOUNTER_H_

class ReferenceCounter
{
public:
  ReferenceCounter();
  virtual ~ReferenceCounter();

public:
  void addReference();
  int release();

private:
  int _count;
};

#endif /* _REFERENCECOUNTER_H_ */
