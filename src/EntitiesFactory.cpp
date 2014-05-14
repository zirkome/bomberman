#include "EntitiesFactory.hpp"

EntitiesFactory *EntitiesFactory::_instance = NULL;

EntitiesFactory *EntitiesFactory::getInstance()
{
  if (_instance == NULL)
    _instance = new EntitiesFactory;
  return _instance;
}
