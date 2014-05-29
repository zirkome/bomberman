#ifndef PLACEMENT_HPP_
#define PLACEMENT_HPP_

#include "Map.hpp"
#include "Fault.hpp"

class Placement
{
private:
  int _numberPlayer;
  int _div;
  glm::vec2 _mapSize;
  Map *_map;
  glm::vec2 const genNewPos();
  bool checkSpace(glm::vec2 const &pos, glm::vec2 const &back, int rec);
  glm::vec2 const foundCloserGoodPlace(glm::vec2 const &pos);
public:
  Placement(Map *_map);
  ~Placement();
  glm::vec2 const getNewPos();
};

#endif
