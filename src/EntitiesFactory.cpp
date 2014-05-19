#include "EntitiesFactory.hpp"

EntitiesFactory *EntitiesFactory::_instance = NULL;

EntitiesFactory *EntitiesFactory::getInstance()
{
  if (_instance == NULL)
    _instance = new EntitiesFactory;
  return _instance;
}

IEntity		*EntitiesFactory::create(IEntity::Type type, int x, int y)
{
  switch (type)
    {
    case IEntity::BOX:
      return new Box(glm::vec2(x, y));
    case IEntity::WALL:
      return new Wall(glm::vec2(x, y));
    case IEntity::GROUND:
      return new Ground(glm::vec2(x, y));
    default:
      return NULL;
    }
}
