#ifndef _SHAREDPOINTER_H_
# define _SHAREDPOINTER_H_

# include <cstdlib>

# include "ReferenceCounter.hpp"

template <class T, class R = ReferenceCounter>
class SharedPointer
{
private:
  T *_ptr;
  R *_ref;

public:
  SharedPointer()
  : _ptr(NULL), _ref(NULL)
  {
    _ref = new R();
    _ref->addReference();
  }

  SharedPointer(T *value)
  : _ptr(value), _ref(NULL)
  {
    _ref = new R();
    _ref->addReference();
  }

  SharedPointer(const SharedPointer<T>& sp)
  : _ptr(sp._ptr), _ref(sp._ref)
  {
    _ref->addReference();
  }

  ~SharedPointer()
  {
    if (_ref->release() == 0)
      {
		delete _ptr;
		delete _ref;
      }
  }

  T& operator*()
  {
    return *_ptr;
  }

  T* operator->()
  {
    return _ptr;
  }

  SharedPointer<T>& operator=(const SharedPointer<T>& sp)
  {
    if (this != &sp)
      {
		if (_ref->release() == 0)
		  {
			delete _ptr;
			delete _ref;
		  }
		_ptr = sp._ptr;
		_ref = sp._ref;
		_ref->addReference();
      }
    return *this;
  }
};

class _shared_null_ptr_type {
public:
  template<typename T>
  operator SharedPointer<T>() { return SharedPointer<T>(); }
};

extern _shared_null_ptr_type null_ptr;

#endif /* _SHAREDPOINTER_H_ */
