#ifndef MAP_HPP_
#define MAP_HPP_

#include <string>
#include <vector>
#include "IEntity.hpp"

class Map
{
private:
  std::vector<std::vector<IEntity *> > _map;
public:
  Map(std::string const &mapFileName);
  ~Map();
};

#endif
