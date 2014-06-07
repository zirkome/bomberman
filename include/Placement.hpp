#ifndef PLACEMENT_HPP_
# define PLACEMENT_HPP_

# include "Map.hpp"
# include "Fault.hpp"

class Placement
{
private:
  int _numberPlayer;
  int _div;
  glm::ivec2 _mapSize;
  Map *_map;
  glm::ivec2 const genNewPos();
  bool checkSpace(glm::ivec2 const &pos, glm::ivec2 const &back, int rec);
  glm::ivec2 const foundCloserGoodPlace(glm::ivec2 const &pos);
public:
  Placement(Map *_map);
  ~Placement();
  glm::vec2 const getNewPos();
};

#endif
