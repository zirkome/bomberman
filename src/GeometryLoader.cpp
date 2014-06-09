#include "GeometryLoader.hpp"

#include <iostream>

AGeometry *GeometryLoader::loadFromFile(const std::string& path)
{
  AGeometry *ptr = new AGeometry(path);

  std::cout << path + " has been loaded" << std::endl;

  return ptr;
}
