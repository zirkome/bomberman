#ifndef _SINGLETON_H_
# define _SINGLETON_H_

# include "ScopeLock.hpp"
# include "PMutex.hpp"

template <class T>
class Singleton
{
protected:
  static T* _singleton;
  static IMutex *_mutex;

public:
  // Here is the why I tricked the code on this method:
  // http://come-david.developpez.com/tutoriels/dps/?page=Singleton#L4-a-3
  static T* getInstance()
  {
    if (_singleton == NULL)
      {
	ScopeLock lock(*_mutex);
        if (_singleton == NULL)
	  {
	    _singleton = static_cast<T*>(operator new(sizeof(T)));
	    new (_singleton) T;
	  }
      }
    return _singleton;
  }

  static void kill()
  {
    delete _singleton;
    _singleton = NULL;
  }

private:
  T& operator=(const T&) {}
};

template <class T> IMutex* Singleton<T>::_mutex = new PMutex;
template <class T> T* Singleton<T>::_singleton = NULL;

#endif /* _SINGLETON_H_ */
