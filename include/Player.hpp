#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "Map.hpp"

class Player
{
private:
  int x;
  int y;
public:
  Player(Map *currentMap);
  ~Player();
};

#endif
