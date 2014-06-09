#include "GeometryLoader.hpp"

#include <iostream>

#include "Cube.hpp"
#include "Cube6Face.hpp"
#include "Pan.hpp"

GeometryLoader::GeometryLoader()
{
  _funcMap["cube.geo"] = &GeometryLoader::instanciateGeometry<Cube>;
  /*s _funcMap["cube6Face.geo"] = &GeometryLoader::instanciateGeometry<Cube6Face>;
   _funcMap["pan.geo"] = &GeometryLoader::instanciateGeometry<Pan>;*/
}

AGeometry *GeometryLoader::loadFromFile(const std::string& type) const
{
  AGeometry *ptr;

  ptr = (this->*(_funcMap.at(type)))();
  std::cout << type + " has been loaded" << std::endl;

  return ptr;
}

