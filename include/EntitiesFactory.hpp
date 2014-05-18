#ifndef _OBJECTFACTORY_H_
#define _OBJECTFACTORY_H_

#include <Texture.hh>
#include <map>
#include "Box.hpp"
#include "Wall.hpp"
#include "Ground.hpp"
#include "IEntity.hpp"

class			EntitiesFactory
{
public:
  static EntitiesFactory	*_instance;
  static EntitiesFactory	*getInstance();
  IEntity			*create(IEntity::Type type, int x, int y);
};

#endif /* _OBJECTFACTORY_H_ */
