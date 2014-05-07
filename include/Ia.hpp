#ifndef IA_HPP_
#define IA_HPP_

#include <string>
#include "Map.hpp"

class Ia
{
public:
  Ia(std::string const &fileName, Map *currentMap);
  Ia(Map *currentMap);// ia basic if we have no files
  ~Ia();
};

#endif
