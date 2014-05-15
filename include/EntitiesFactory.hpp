#ifndef _OBJECTFACTORY_H_
#define _OBJECTFACTORY_H_

#include <Texture.hh>
#include <map>
#include "IEntity.hpp"

class			EntitiesFactory
{
public:
  static EntitiesFactory	*_instance;
  static EntitiesFactory	*getInstance();
  template <class T>
  IEntity			*create(int x, int y)
  {
    return new T(x, y);
  }
};

#endif /* _OBJECTFACTORY_H_ */
